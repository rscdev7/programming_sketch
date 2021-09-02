%
% @author    :     rscalia
% @date      :     Fri 02/04/2021
%
% This module implements some routine about some linear algebra computations.
%

-module(lin_alg).
-export([dotProduct/2 , matVecMul/2, reduceList/1]).



%Effettua il prodotto scalare fra due vettori di R^n
dotProduct (V1, []) -> 
    []
;
dotProduct([],V2) ->
    []
;
dotProduct (V1,V2) ->
    if (length(V1) /= length(V2) ) -> shapeRuntimeError

    ; (length(V1) == length(V2))  ->   DotProductPairs   = lists:zip(V1,V2),
                                       MulList           = mapList(DotProductPairs),
                                       DotP              = reduceList(MulList)
                    
                                       
    end
.

%Computa le moltiplicazioni necessarie al prodotto scalare
mapList ([]) -> [];
mapList ( [ {A,B} ] ) -> [A*B];
mapList ([ {A,B} | T]) -> [A*B | mapList(T)]
.

%Computa la sommanecessaria al prodotto scalare
reduce (C,[]) -> C;
reduce ( C, [H|T] ) -> reduce (C+H, T)
.

reduceList (H) -> reduce(0,H).



%Applicazione Lineare f_M : R^m ---> R^n attraverso un'apposita matrice di trasformazione
matVecMul (M, [[]] )  -> []
;
matVecMul ( [[]] , V) -> []
;
matVecMul (M,V) ->
    Is_dense = isDenseMatrix(M),
    Mtr_dim  = extractMtrDim(M),

    if (Is_dense == false)      -> sparseMatrixRuntimeError
    ; (length(V) /= Mtr_dim)    -> shapeRuntimeError
    ; (length(V) == Mtr_dim)    -> matrixVectorMultiplication(M,V) 
    end
.

%Predicato per controllare se una matrice è densa
isDenseMatrix ( [[]] )  -> true
;
isDenseMatrix ( [] )    -> true
;
isDenseMatrix ( [ H ] ) -> true
;
isDenseMatrix ([ H1 | [H2 | T] ]) -> if (length(H1) == length (H2)) -> isDenseMatrix(T)
                                     ; (length(H1) /= length (H2))  -> false
                                     end
.

%Prelievo dimensione interna matrice
extractMtrDim (M) ->
    H = fun([M|T]) -> length(M) end , H(M)
.

%Moltiplica una matrice per un vettore
matrixVectorMultiplication ([H],V) -> [dotProduct(H,V)]
;
matrixVectorMultiplication ([H|T],V) -> [dotProduct(H,V) | matrixVectorMultiplication(T,V)]
.