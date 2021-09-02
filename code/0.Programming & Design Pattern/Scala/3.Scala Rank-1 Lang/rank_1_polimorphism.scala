//Il Polimorfismo Parametrico di Scala è Rank-1
//Questo significa che posso avere una singola quantificazione Universale
//Al livello di singola Dichiarazione di Funzione

scala> def g[A] (f:A=>List[A],arg:A):List[A] = f(arg)
def g[A](f: A => List[A], arg: A): List[A]

scala> def f[A](a:A):List[A] = List(a)
def f[A](a: A): List[A]

//Non compila perchè 
// 1) g(.) è (f:A => List[A] , arg:A) => List[A]  
// 2) f(.) è (f:A) => List[A]  
// Ma siccome f è dentro g, succede che POSSO passare a f SOLAMENTE lo stesso A dichiarato
//in g
// Per tanto, nei linguaggi rank-1 abbiamo una sola quantificazione Universale, che sta all'esterno della funzione "più esterna" che è stata definita
scala> g[Float](f,true)
         ^
       error: type mismatch;
        found   : Boolean(true)
        required: Float