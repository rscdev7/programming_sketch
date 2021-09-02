%
% @author    :     rscalia
% @date      :     Fri 02/04/2021
%
% This module implements the inference compuation of a Multi-Layer Perceptron (MLP) having fixed-weights and 3 Hidden Layer.
%
% Moreover, the final layer of the network outputs a Probability Distribution over 3 class, say A,B and C.
%

-module(mlp).
-export ([setup/0, managerInit/0 , layerComputation/3]).
-import(lin_alg, [matVecMul/2,reduceList/1]).
-import(math,[exp/1]).

-define (W1,        [
                            [ 0.05816783, -0.97912185, -0.00365445,  0.11508815],
                            [-0.03949785,  0.31717917, -1.22509005, -0.60799364],
                            [-0.88730265,  0.21766486, -1.31756816, -0.20017542],
                            [-0.73076375, -0.4332535 , -1.28388995, -2.3072264 ],
                            [ 1.13078581,  0.56151508, -0.64131625,  0.15405599]
                    ]).

-define (W2,        [
                            [ 0.18394179, -0.08455657, -0.59680949, -1.34305971,  1.04836284],
                            [-0.42670929, -2.39640155, -0.5734874 , -1.22353287, -0.65955532],
                            [ 0.31155219, -0.21489464, -0.02783284,  0.33275142, -0.08245383],
                            [-1.68645165,  0.00817835, -0.12059848,  0.40904893, -0.47743386],
                            [ 1.51587734, -0.31250684,  0.23650486,  0.82757099, -0.25211682],
                            [-0.90589431, -0.39765551, -0.02862974, -0.01733783,  0.68439701],
                            [-0.93030789, -1.37362905, -0.68029457,  0.12415801,  0.57323285]
                    ]).

-define(W3,         [   
                            [ 1.99558546, -1.65904494, -1.61548954, -1.23848952,  0.1531495 , 0.35375079,  0.58049189],
                            [ 0.21342507,  0.92107264,  0.40768069, -0.04733957, -1.5140687 , 1.2779766 , -0.41899066],
                            [-1.26357911,  1.21692508,  2.39892631,  0.09465238,  0.79108254, -0.93544072,  0.91744663]
                    ]).


%Build actors and initialize their params
setup() -> 
            %Actors build
            RefManager = spawn(mlp,managerInit,[]),

            RefH3      = spawn(mlp,layerComputation,[RefManager,output_layer,none]),
            RefH2      = spawn(mlp,layerComputation,[none,middle_layer, RefH3]),
            RefH1      = spawn(mlp,layerComputation,[RefManager, input_layer, RefH2]),

            %Send First layer ID to the Manager
            RefManager ! RefH1,

            %Returning reference of manager to the client
            RefManager
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
layerComputation(IDManager, LayerType, NextLayerID) ->

    receive
        {computeReq, OriginalData, CurrentData, RefClient} ->

            if (LayerType == input_layer) -> 
                RES     = lin_alg:matVecMul(?W1, CurrentData),

                if ( RES /= shapeRuntimeError ) ->
                    NextLayerID ! {computeReq,OriginalData,RES,RefClient}

                ; ( RES == shapeRuntimeError ) ->
                    IDManager ! {error, RefClient, OriginalData, RES}

                end

            ; (LayerType == middle_layer) -> 
                RES     = lin_alg:matVecMul(?W2, CurrentData),
                NextLayerID ! {computeReq,OriginalData,RES,RefClient}

            ; (LayerType == output_layer) -> 
                RES     = lin_alg:matVecMul(?W3, CurrentData),
                N_RES   = softmax(RES),
                IDManager ! {inferenceResult, RefClient, OriginalData, N_RES}
            end
    end,

    layerComputation(IDManager, LayerType, NextLayerID)
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