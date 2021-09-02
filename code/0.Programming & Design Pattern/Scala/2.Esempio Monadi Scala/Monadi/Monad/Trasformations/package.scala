package Monad.Trasformations

import Monad._

package object Trasform {

    def fun_1 (arg:ComputationStatus[Int]):LazyMonad[ComputationStatus[Float]]   = {
        val k = ComputationStatus[Float]( arg.internal.toFloat / 40  , "consistent" )
        LazyMonad.unit(k)
    }

    def fun_2 ( arg:ComputationStatus[Float] ):LazyMonad[ComputationStatus[Int]]   = {
        val cp_current_val:Float = arg.internal

        cp_current_val match {
            case x if x > 1000.0            => LazyMonad.unit( ComputationStatus[Int]    (0  , "unconsistent"     )     )
            case (_)                        => LazyMonad.unit( ComputationStatus[Int]    (50 , "consistent"       )     )
        }
    }

}