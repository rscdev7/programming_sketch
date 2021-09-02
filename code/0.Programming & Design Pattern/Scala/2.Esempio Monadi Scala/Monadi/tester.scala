/*
@author    :     rscalia
@date      :     Wed 28/04/2020

Esempio di Monade in Scala
*/


import Monad._
import Monad.Trasformations.Trasform._ 



object Main extends App {

    //Input della Computazione
    val INPUT:Int   = 50000   
    val monad       = LazyMonad


    //Inizializzazione della Computazione
    val init_compute_value:ComputationStatus[Int]                   = ComputationStatus[Int](INPUT,"consistent")
    val init:LazyMonad[ComputationStatus[Int]]                      = monad.unit  (init_compute_value)
    

    //Step 1 della Computazione
    val step_1:LazyMonad[ComputationStatus[Float]]                  = init.flatMap{ fun_1 }


    //Step 2 della Computazione
    val step_2:LazyMonad[ComputationStatus[Int]]                    = step_1.flatMap{ fun_2 }
    step_2.get match {
        case ComputationStatus (internal,"consistent")      => println ("\n[!] Outcome Computation: "+internal+" \n")
        case ComputationStatus (_,"inconsistent")           => println ("\n[x] Computation Status is Inconsistent :(\n")
        case _                                              => println ("\n[x] Computation Status is Inconsistent :(\n")
    }
    
}