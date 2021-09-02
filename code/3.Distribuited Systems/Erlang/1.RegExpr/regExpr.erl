% An Erlang program simulating a finite state machine
% recognizing the regular language represented by the regular expression
% abc*+c(bb)*.
% Each state has to be represented by a process.
% (by F.Barbanera)

-module(regExpr).
-export([manager/0,state/2,create/0]).

% Module for automaton for a regular languages on {a,b,c}.
%
% Each state is a process. Many strings can be parsed in parallel. 
%
% create : creates a particular automaton (the one corresponding to (ab)* in this simple example)
%                   together with its manager. 
%
%          A parsing request can be sent to the manager by means of a triple {requestParsing,ID,List}
%          where ID is the PID of whom makes the request, and List is the string to be parsed.
%
%          For sake of simplicity a string is represented by a list of atoms that represents characters.
%
%          The manager sends the request to the initial state and receives the answer that is then
%          delivered to whom made the request. 
%          The original string to be parsed is kept through all the parsing process and sent back with the 
%          answer in order one can send onother request even before one gets the answer of the previous request. 
%
% manager : It is the function corresponding to the manager of the automaton.
%          Once spawned by the create function, the manager waits for the address of the initial state, 
%          that the create function itself sends to it (This procedures is a simple trick necessary since
%          the manager and the initial state need the PID of each other.)
%
% state   : It is the function corresponding to a state. Its arguments are the PID of the manager
%           and one atom (final or nofinal) representing whether the spawned state is final or not.
%           Once spawned by the create function, a state waits for a triple of PIDs
%           corresponding, respectively, to the states it has to be connected to for the characters a, b, or c.
%           In case a state is not connected to another state for a particular character (and hence the
%           string has to be rejected), the corresponding element in the triple is the atom none instead of a PID.
%           (As for the manager, this trick is needed in order to have automata with cliques.          

%% abc*+c(bb)*
%
%       a    b   c       Final States = q2, q3
% init  q1       q3
%   q1      q2 
%   q2           q2     
%   q3      q4
%   q4      q3
%


create () ->          %%we create the manager and the (process-)states. The PID of manager is returned.

                      IDmanager = spawn(regExpr,manager,[]),
                      IDinit    = spawn(regExpr,state,[IDmanager,notfinal]),
                      IDq1      = spawn(regExpr,state,[IDmanager,notfinal]),
                      IDq2      = spawn(regExpr,state,[IDmanager,final]),
                      IDq3      = spawn(regExpr,state,[IDmanager,final]),
                      IDq4      = spawn(regExpr,state,[IDmanager,notfinal]),

                      %%we connect the manager to qinit and the various states among themselves

                      IDmanager!IDinit,
                      IDinit!{IDq1,none,IDq3},
                      IDq1!{none,IDq2,none},
                      IDq2!{none,none,IDq2},
                      IDq3!{none,IDq4,none},
                      IDq4!{none,IDq3,none},
                      IDmanager.
                      


manager() -> receive
               IDinitial -> loopmanager(IDinitial)
             end.                       
                   

loopmanager(IDinitial) ->
             
               receive

                   {requestParsing,ID,List} -> IDinitial ! {List,ID,List};
                                               
                   {accepted,ID,List}       -> ID ! {accepted,List};

                   {rejected,ID,List}       -> ID ! {rejected,List}

               end,
             
               loopmanager(IDinitial).




                    


state(IDmanager,Final) -> receive
                             {IDA,IDB,IDC} -> loop(IDA,IDB,IDC,IDmanager,Final) 
                          end. 




 loop(IDA,IDB,IDC,IDmanager,Final) ->
           
         
         receive

              {[],ID,List}          ->    if 
                                             (Final == final)  -> IDmanager ! {accepted,ID,List};
                            
                                              true             -> IDmanager ! {rejected,ID,List}
                     
                                          end;

              {[ Char | Cs ],ID,List}  ->  Next = (if (Char == a) -> IDA; (Char == b) -> IDB; (Char == c) -> IDC; (Char == Char) -> none end),
                                           
                                           if
                                              (Next == none)    ->  IDmanager ! {rejected,ID,List};

                                               true             -> Next ! {Cs,ID,List}
                                           end
          end,
             
         loop(IDA,IDB,IDC,IDmanager,Final).


% The above program can be modified in order the function create takes the description of
% a finite automaton (its transition table) and returns the PID of the manager of the 
% corresponding system. Such a program is described in the solution of Exercise 14 in
% http://www.dmi.unict.it/~barba/PROG-LANG/ESERCIZI/EserciziActorsErlang/esercizi.html


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
