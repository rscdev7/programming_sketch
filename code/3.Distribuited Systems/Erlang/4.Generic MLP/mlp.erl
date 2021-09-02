%
% @author    :     rscalia
% @date      :     Fri 02/04/2021
%
% This module implements the inference compuation of a Multi-Layer Perceptron (MLP) having fixed-weights and 3 Hidden Layer.
%
% Moreover, the final layer of the network outputs a Probability Distribution over 3 class, say A,B and C.
%

-module(mlp).
-export ([setup/1, buildNNLayers/4, managerInit/0 , layerComputation/4]).
-import(lin_alg, [matVecMul/2,reduceList/1]).
-import(math,[exp/1]).


%Build actors and initialize their params
%LayersWeights is a list of matrix ranging from first-layer to last_layer
setup(LayersWeights) -> 
            %Actors build
            RefManager              = spawn(mlp,managerInit,[]),

            InvertedLayersWeights   = lists:reverse(LayersWeights),
            ReversePids             = buildNNLayers(InvertedLayersWeights, RefManager, output_layer, none),
            Pids                    = lists:reverse(ReversePids),


            %Send First layer ID to the Manager
            RefManager ! lists:nth(1,Pids),

            %Returning reference of manager to the client
            RefManager
.            


%Dinamycaly, builds a set of Linear Layer starting from a list of Matrix Weights
buildNNLayers ( [M] , RefManager, LayerType , NextLayerID ) ->
    ID      = spawn(mlp,layerComputation, [RefManager, input_layer, NextLayerID, M]),
    [ID]
;
buildNNLayers ( [H | T] , RefManager, LayerType , NextLayerID ) ->
    ID      = spawn(mlp,layerComputation, [RefManager, LayerType, NextLayerID, H]),
    [ ID | buildNNLayers(T, RefManager , middle_layer , ID )  ]
.


%Wrapper to manager computation, here we pass the reference of the Input Layer
managerInit() ->    receive
                        RefInputLayer -> managerComputation(RefInputLayer)
                    end
.

%Manager Computation
managerComputation (RefInputLayer) ->
                    receive 
                        {requestInference, RefClient, VEC}       -> RefInputLayer   ! {computeReq, VEC, VEC, RefClient};
                        {inferenceResult,RefClient, Input, Res}  -> RefClient       ! {result, Input,Res};
                        {error,RefClient, Input, Error}          -> RefClient       ! {error, Input,Error}
                     end,

                    managerComputation(RefInputLayer)
.


%MLP-Layer Computations
layerComputation(IDManager, LayerType, NextLayerID, Weights) ->

    receive
        {computeReq, OriginalData, CurrentData, RefClient} ->

            if (LayerType == input_layer) -> 
                RES     = lin_alg:matVecMul(Weights, CurrentData),

                if ( RES /= shapeRuntimeError ) ->
                    NextLayerID ! {computeReq,OriginalData,RES,RefClient}

                ; ( RES == shapeRuntimeError ) ->
                    IDManager ! {error, RefClient, OriginalData, RES}

                end

            ; (LayerType == middle_layer) -> 
                RES     = lin_alg:matVecMul(Weights, CurrentData),
                NextLayerID ! {computeReq,OriginalData,RES,RefClient}

            ; (LayerType == output_layer) -> 
                RES     = lin_alg:matVecMul(Weights, CurrentData),
                N_RES   = softmax(RES),
                IDManager ! {inferenceResult, RefClient, OriginalData, N_RES}
            end
    end,

    layerComputation(IDManager, LayerType, NextLayerID, Weights)
.


%This set of methods implement the softmax operator
expList ([A]) -> [exp(A)]
;
expList ([H | T]) -> [exp(H)|expList(T)]
.

swDiv ([A],LogitsSum)   -> [A/LogitsSum]
;
swDiv ([H|T] , LogitsSum) -> [H/LogitsSum | swDiv(T,LogitsSum)]
.

stabilizeData ([H],M) -> [H-M]
;
stabilizeData ([H | T],M) -> [H-M | stabilizeData(T,M)]
.

softmax (A) ->
    MAX         = lists:max(A),
    StableData  = stabilizeData(A,MAX),
    ExptList    = expList(StableData),
    LogitsSum   = lin_alg:reduceList(ExptList),
    swDiv(ExptList , LogitsSum)
.