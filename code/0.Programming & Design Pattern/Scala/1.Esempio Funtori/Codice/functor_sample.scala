//Definizione "Super" Categoria Nature  e classe Leone
//Serviranno per mostrare i costraint sui Sottotipi
abstract class Nature {
    def nome:String
}

case class Leone (nome:String) extends Nature


//Definizione Categoria Animale 
//Stiamo interpretando le Categorie come Tipi
abstract class Animale extends Nature

//Definizione Categoria Gatto 
//Definizione Funtore <: Animale ---> Gatto
//Interpretiamo l'Ereditarieta' come Sottotipo 
//Tale interpretazione rimane Impropria in senso Assoluto 
//Cio' nonostante, per Scala i Sottotipo e l'Ereditarieta' 
//   sono la stessa cosa
//Link Uguaglianza Sottotipo-Ereditarieta' Scala: 
//   https://docs.scala-lang.org/tour/upper-type-bounds.html
case class Gatto (nome:String) extends Animale


//Definizione Morfismo Contenitore  
//  Il Sottotipo e' Covariante rispetto a quest'ultimo
case class Contenitore[+A<:Animale] (animal: A)


//Definizione Entry-Point Programma (Main)
object Main extends App {

    //Testa Covarianza Funtore rispetto al Morfismo
    def testFunctor (ct:Contenitore[Animale]):Unit = {
        println(ct.animal.nome)
    }

    val cat:Gatto                      = Gatto("Poldo")
    val ct:Contenitore[Gatto]          = Contenitore[Gatto](cat)
    testFunctor(ct)

    //Le seguenti righe portano ad un Errore di Compilazione
    /* val lion:Leone             = Leone("Simba")                        */
    /* val wrongContainer         = Contenitore[Leone](lion)              */
}