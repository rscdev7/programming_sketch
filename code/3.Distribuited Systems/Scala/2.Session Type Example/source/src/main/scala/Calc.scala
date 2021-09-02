import scala.concurrent.duration.Duration
import lchannels._
import lchannels.LocalChannel.parallel
import scala.concurrent.Await
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.duration._

/////////////////////////////////////////////////////////////////////////////
// Session type:
// ?Welcome(Str) . rec X . (+) { !Negate(Int) . ?Answer(Int) . X ,
//                               !Add(Int) . !Add2(Int) . ?Answer(Int) . X ,
//                               !Quit() }
/////////////////////////////////////////////////////////////////////////////
sealed case class Welcome(message: String)(val cont: Out[Choice])

sealed abstract class Choice
case class Negate(value: Integer)(val cont: Out[Answer]) extends Choice
case class Add(value1: Integer)(val cont: In[Add2])      extends Choice
case class Quit()                                        extends Choice

sealed case class Add2(value2: Integer)(val cont: Out[Answer])

sealed case class Answer(value: Integer)(val cont: Out[Choice])
/////////////////////////////////////////////////////////////////////////////



object Server {

  def apply(c: Out[Welcome]) (implicit timeout: Duration): Unit = {

    println(f"[S] Sending welcome to ${c}...")
    val c2    = c !! Welcome("Welcome to SessionCalc 0.1")_
    subHandler(c2)


    def subHandler(c: In[Choice]) {
    
      println("[S] Now waiting for a choice... ")

      c ? {

        case Quit() => {
          println(f"[S] Got Quit(), finishing")
        }

        case m @ Negate(value) => {
          println(f"[S] Got 'Negate(${value})', answering ${-value}")

          val c2 = m.cont !! Answer(-value)_

          println("[S] Performing recursive call...")
          subHandler(c2)
        }

        case m @ Add(val1) => {

          println(f"[S] Got Add(${val1}), waiting for 2nd value...")

          m.cont.receive match {

            case m @ Add2(val2) => {
              println(f"[S] Got Add2(${val2}), answering ${val1 + val2}...")
              val c3 = m.cont !! Answer(val1 + val2)_

              println("[S] Performing recursive call...")
              subHandler(c3)
            }

          }

        }

      }

    }
  }
}

object Client {

  def apply(c: In[Welcome]) (implicit timeout: Duration): Unit = {

    val welcome   = c.receive
    println(f"[C] Got '${welcome.message}'")
    println(f"[C] Sending Negate(42)...")


    val ans       = welcome.cont !! Negate(42)_
    println("[C] ...done.  Now waiting for answer...")


    val neg       = ans.receive
    println(f"[C] ...done: got ${neg.value}")
    println("[C] Now trying to add 7 and 5...")
  

    val ans2      = neg.cont !! Add(7)_ !! Add2(5)_
    println("[C] ...done.  Now waiting for answer...")


    val sum       = ans2.receive
    println(f"[C] ...done: got ${sum.value}")
  

    println("[C] Now quitting")
    sum.cont ! Quit()
  }
}

object Local extends App {

  // Helper method to ease external invocation
  def run() = main(Array())
  implicit val timeout = 5.seconds
  

  println("[*] Spawning local server and client...")
  val (s, c) = parallel[Welcome, Unit, Unit](
    Client(_), Server(_)
  )

  // Wait for server termination
  Await.result(s, 10.seconds) 
}