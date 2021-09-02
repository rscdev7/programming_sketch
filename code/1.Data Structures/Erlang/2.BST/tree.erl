%
% @author    :     rscalia
% @date      :     Thu 25/03/2021
%
% Questo modulo implementa un albero binario di ricerca in Erlang.
% Inoltre, il modulo costruisce l'albero sfruttando le seguenti assunzioni:
%
% 1) Empty Tree: { {}, {} , {} } 
% 2) First Tuple is the Root
% 3) Secondo Tuple is the Leff-Subtree
% 4) Third Tuple is the Right-Subtree
%
% Infine, il modulo supporta le seguenti operazioni sugli alberi:
%
% 1) Inserimento
% 2) Cancellazione
% 3) Ricerca
% 4) Visitia InOrder
% 5) Massimo di un Albero
% 6) Minimo di un Albero


-module(tree).
-export([initTree/1, insert_value/2, inOrder/1, search/2, maxT/1, minT/1, delete/2, getRoot/1]).



%Inizializza un albero/sottoalbero vuoto
initTree (K) ->
    {K,{},{}}
.


%Caso Inserimento su albero vuoto
insert_value(Tree = {R,{},{}}, K) ->
    if K > R -> 
        {R, {}, initTree(K)  }

    ; K =<  R -> {R, initTree(K) , {}}
    end
;
%Caso Inserimento su albero avente solo figlio sinistro
insert_value(Tree = {R,LT,{}}, K) ->
    if K > R -> 
        {R,LT, initTree(K) }
    ; K =<  R -> {R,insert_value(LT,K), {} }
    end
;
%Caso Inserimento su albero avente solo figlio destro
insert_value(Tree = {R,{},GT}, K) ->
    if K > R -> 
        {R,{},insert_value(GT,K)}
    ; K =<  R -> {R, initTree(K) , GT }
    end
;
%Caso Inserimento su Albero avente figlio destro e sinistro
insert_value(Tree = {R,LT,GT}, K) ->
    if K > R -> 
        {R,LT,insert_value(GT,K)}
    ; K =<  R -> {R,insert_value(LT,K),GT}
    end
.


%Ricerca
search (K, Tree={R,{},{}}) ->
    if K == R ->
        true
    ; K /= R -> false
    end
;
search (K, Tree={}) ->
    false
;
search (K, Tree= {R, {SX,{},{}} , {RX,{},{}} } )  ->
    if K == R ->
        true
    ; K == SX -> true
    ; K == RX -> true
    ; (K /= R) and (K /= RX) and (K /= SX) -> false 
    end
;
search (K, Tree={R,LT,GT}) ->
    if (K==R) -> true
    ; K > R -> search(K, GT)
    ; K =< R -> search(K,LT)
    end
.


%Cancellazione
delete (K, Tree={R,{},{}}) ->
    if K == R ->
        {}
    ; K /= R -> Tree
    end
;
delete (K, Tree={}) ->
    Tree
;
delete (K, Tree= {R, {SX,{},{}} , {RX,{},{}} } )  ->
    if K == R ->
        {RX, {SX,{},{}} , {} }
    ; K == SX -> {R, {} , {RX,{},{}} }
    ; K == RX -> {R, {SX,{},{}} , {} }
    ; (K /= R) and (K /= RX) and (K /= SX) -> Tree 
    end
;
delete (K, Tree={R,LT,GT}) ->
    if (K==R) -> {minT(GT) , LT, delete(minT(GT),GT) }
    ; K > R -> {R,LT,delete(K, GT)}
    ; K =< R -> {R,delete(K,LT),GT}
    ; (K /= R) -> Tree 
    end
.


% Prelievo Radice
getRoot (Tree={R,LT,GT}) ->
    R.


% Massimo di un albero
maxT (Tree={R,{},{}} ) ->
    R
;
maxT (Tree={R,LT,{}} ) ->
    R
;
maxT (Tree={R,LT,{RX,{},{}} } ) ->
    RX
;
maxT (Tree={R,LT, {RX, RSX, RRX}} ) ->
    maxT(RRX)
.

% Minimo di un albero
minT (Tree={R,{},{}} ) ->
    R
;
minT (Tree={R,{},GT} ) ->
    R
;
minT (Tree={R,{SX,{},{}} , GT } ) ->
    SX
;
minT (Tree={R,{SX, SSX, SRX} , GT} ) ->
    minT(SSX)
.



%Visite InOrder Albero su caso albero vuoto
inOrder (Tree= {{},{},{}}) ->
    []
;
inOrder (Tree= {}) ->
    []
;
%Visite InOrder Albero su caso albero con la sola radice
inOrder(Tree={R , {} , {}  }) ->
    [R]
;
%Visite InOrder Albero su caso albero avente radice e una foglia sinistra
inOrder(Tree={R , {SX,{},{}} , {}  }) ->
    [SX,R]
;
%Visite InOrder Albero su caso albero avente radice e una foglia destra
inOrder(Tree={R , {} , {RX,{},{}}  }) ->
    [R,RX]
;
%Visite InOrder Albero su caso albero avente radice e entrambe le foglie
inOrder(Tree={R , {SX,{},{}} , {RX,{},{}}  }) ->
    [SX,R,RX]
;
%Visite InOrder Albero su caso albero avente due sottoalberi come figli desto e sinistro
inOrder(Tree={R,LT,GT}) ->
    inOrder(LT)++[R]++inOrder(GT)
.