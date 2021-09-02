-module(startup).
-export([reverse/1, sum/1]).

reverse([]) -> 
    [] 
;
reverse([H|T]) -> 
    reverse(T)++[H]
. 


sum([]) ->
    0
;
sum([H|T]) -> 
    H + sum(T)
.