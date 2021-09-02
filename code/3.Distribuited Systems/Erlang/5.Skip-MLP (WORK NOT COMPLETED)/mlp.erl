%
% @author    :     rscalia
% @date      :     Fri 02/04/2021
%
% This module implements the inference compuation of a Multi-Layer Perceptron (MLP) having fixed-weights and 3 Hidden Layer.
%
% Moreover, the final layer of the network outputs a Probability Distribution over 3 class, say A,B and C.
%

-module(mlp).
-export ([setup/1, managerInit/0 , layerComputation/4]).
-import(lin_alg, [matVecMul/2,reduceList/1]).
-import(math,[exp/1]).


%Build actors and initialize their params
%LayersWeights is a list of matrix ranging from first-layer to last_layer
setup(LayersWeights) -> 
            %Actors build
            RefManager              = spawn(mlp,managerInit,[]),

            InvertedLayersWeights   = lists:reverse(LayersWeights),
            ReversePids             = buildNNLayers(InvertedLayersWeights, RefManager, output_layer, none ,dict:new(), length(LayersWeights) ),
            Pids                    = lists:reverse(ReversePids),


            %Send First layer ID to the Manager
            RefManager ! lists:nth(1,Pids),

            %Returning reference of manager to the client
            RefManager
.            



%Dinamycaly, builds a set of Linear Layer starting from a list of Layers Specification
buildNNLayers (  [H] , RefManager, LayerType , NextLayerID, BuiltActors, NumberOfLayers) ->
    {WeightsMatrix, InLinks, OutLinks} = H,
    LayerData                          = [WeightsMatrix] ++ [InLinks] ++ [fetchOutLinkConnections( BuiltActors , OutLinks )],

    ID                                 = [ spawn(mlp,layerComputation, [RefManager, input_layer, NextLayerID, LayerData]) ],
    FinalID                            = lists:nth(1,ID),
    io:fwrite("Hello world! ~p,~p ~p ~n", [ID,FinalID,BuiltActors]),

    [ FinalID ]
;
buildNNLayers ( [H | T] , RefManager, LayerType , NextLayerID, BuiltActors, NumberOfLayers ) ->
    {WeightsMatrix, InLinks, OutLinks} = H,
    LayerData           = [WeightsMatrix] ++ [InLinks] ++ [fetchOutLinkConnections( BuiltActors , OutLinks )],

    ID                  = [ spawn(mlp,layerComputation, [RefManager, LayerType, NextLayerID, LayerData]) ],
    FinalID             = lists:nth(1,ID),
    

    CurrentActorIndex   = NumberOfLayers - dict:size(BuiltActors),
    UpdatedActorDict    = dict:store( CurrentActorIndex  , FinalID, BuiltActors),
    io:fwrite("Hello world! ~p,~p ~p ~n", [ID,FinalID,BuiltActors]),

    [ ID | buildNNLayers(T, RefManager , middle_layer , FinalID, UpdatedActorDict, NumberOfLayers  )  ]
.


fetchOutLinkConnections (ActorDicitionary, []) ->
    []
;
fetchOutLinkConnections (ActorDicitionary, [H]) ->
    Ref     = dict:find(H,ActorDicitionary),
    [Ref]
;
fetchOutLinkConnections (ActorDicitionary, [H | T]) ->
    Ref     = dict:find(H,ActorDicitionary),
    [Ref | fetchOutLinkConnections(ActorDicitionary,T) ]
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
                W           = lists:nth(1,Weights),
                OutLinkRef  = lists:nth(3,Weights),
                
                RES         = lin_alg:matVecMul(W, CurrentData),

                if ( RES /= shapeRuntimeError ) ->
                    NextLayerID ! {computeReq,OriginalData,RES,RefClient},
                    propagateSkipOutput(RES,OutLinkRef)
                    

                ; ( RES == shapeRuntimeError ) ->
                    IDManager ! {error, RefClient, OriginalData, RES}

                end


            ; (LayerType == middle_layer) -> 
                W           = lists:nth(1,Weights),
                InLinkRef   = lists:nth(2,Weights),
                OutLinkRef  = lists:nth(3,Weights),

                LayerInput  = assembleFinalLayerInput(InLinkRef, CurrentData),

                RES         = lin_alg:matVecMul(W, LayerInput),

                NextLayerID ! {computeReq,OriginalData,RES,RefClient},
                propagateSkipOutput(RES,OutLinkRef)


            ; (LayerType == output_layer) -> 
                W           = lists:nth(1,Weights),
                InLinkRef   = lists:nth(2,Weights),

                LayerInput  = assembleFinalLayerInput(InLinkRef, CurrentData),

                RES         = lin_alg:matVecMul(Weights, LayerInput),
                N_RES       = softmax(RES),

                IDManager ! {inferenceResult, RefClient, OriginalData, N_RES}

            end
    end,

    layerComputation(IDManager, LayerType, NextLayerID, Weights)
.


assembleFinalLayerInput ([], Data) -> Data
;
assembleFinalLayerInput ([H], Data) -> 
    receive 
        {layer_skip_data , SkipData} -> Z = Data++SkipData, assembleFinalLayerInput([], Z)
    end
;
assembleFinalLayerInput ([H | T], Data) -> 
    receive 
        {layer_skip_data , SkipData} -> Z = Data++SkipData, assembleFinalLayerInput(T, Z)
    end
.


propagateSkipOutput(Output , []) -> empty_recipients
;
propagateSkipOutput(Output , [H]) -> {_,IDX} = H , IDX ! {layer_skip_data , Output}
;
propagateSkipOutput(Output , [H | T]) -> {_,IDX} = H , IDX ! {layer_skip_data , Output}, propagateSkipOutput(Output, T)
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