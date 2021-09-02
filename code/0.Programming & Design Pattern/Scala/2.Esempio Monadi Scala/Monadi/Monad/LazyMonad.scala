package Monad

//Una Monade è una rappresentazione di una Computazione (in termini Funzionali) di natura Sequenziale 
//Quest'ultima può essere caratterizzata anche dalla presente di Effetti Collaterali
// f: A -> Monad[B]         >>      g: B -> Monad[C]        >>      h: C -> Monad[D] ....
class LazyMonad[+A](value:A) {
    private lazy val internal:A                                                                      = value

    def flatMap         [B]  ( f     :A => LazyMonad[B] )               : LazyMonad[B]               = f(internal)
    def get                                                             : A                          = internal
}

object LazyMonad {
    def unit            [A]  ( value  : => A            )               : LazyMonad[A]               = new LazyMonad(value)
}


//L'effetto aggiunto dalla Monade ,in questo caso, sarebbe l'aggiunta di una Stringa ad ogni Output dei passi Computazionali
//della Sequenza. 
//Tale stringa, ci aiuta a comprendere se la computazione sia entratata in uno stato Inconsistente.
case class ComputationStatus[A] (internal:A, status:String)