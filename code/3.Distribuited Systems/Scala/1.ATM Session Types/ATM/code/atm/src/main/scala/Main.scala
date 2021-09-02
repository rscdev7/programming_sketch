/*
@author           	:  rscalia
@version  		    :  1.0.0
@build-date         :  Fri 07/05/2021
@last_update        :  Fri 07/05/2021

Questo componente illustra un'implementazione del Protocollo di un ATM utilizzando i Session-Types su Scala

*/


import scala.concurrent.duration.Duration
import lchannels._
import lchannels.LocalChannel.parallel
import scala.concurrent.Await
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.duration._

/////////////////////////////////////////////////////////////////////////////
// SESSION-TYPE DEF:
//  rec X . (+) {
//                !Login(String) . (&) {
//                                          ?Success() . 
//                                                          (+) {
//                                                                  !Deposit(Integer)  .  ?Balance(Integer) 		. X
//                                                                  !Withdraw(Integer) .  (&) {
//                                                                                                ?Dispense  ()  	. X
//                                                                                                ?OverDraft () 	. X
//                                                                                            }
//																	!Exit()
//                                                              }
//                                          ?Failure() .    X
//                                     }
//                !Quit()
//              }
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//SESSION-TYPE IMPLEMENTAZIONE 

//Layer 1
sealed abstract class ClientChoice
case class Login ( pin:String ) ( val cont:Out[ServerLoginResponse] )             	extends ClientChoice
case class Quit  (            )                                                  	extends ClientChoice


//Layer 2
sealed abstract class ServerLoginResponse
case class Success () ( val cont:   Out[Menu]          )                        	extends ServerLoginResponse
case class Failure () ( val cont:   Out[ClientChoice]  )                        	extends ServerLoginResponse


//Layer 3
sealed abstract class Menu
case class Deposit  ( value:Integer ) ( val cont: Out[Balance] )                    extends Menu
case class Withdraw ( value:Integer ) ( val cont: Out[ServerWithDrawResponse] )     extends Menu
case class Exit     (               )											   	extends Menu


//Layer 4
sealed case class Balance( value:Integer ) ( val cont:Out[ClientChoice] )

sealed abstract class ServerWithDrawResponse 
case class Dispense  () ( val cont:  Out[ClientChoice] )                         	extends ServerWithDrawResponse
case class OverDraft () ( val cont:  Out[ClientChoice] )                         	extends ServerWithDrawResponse
///////////////////////////////////////////////////////////////////////////// 


//Codice Server
object ATM {

	def apply(channel_end: In[ClientChoice]) (implicit timeout: Duration): Unit = serverRecursiveHandler(channel_end)

	def serverRecursiveHandler (channel_end: In[ClientChoice]) (implicit timeout: Duration) : Unit = {

		channel_end ? {

			case Quit() => {
          		println("\n[SERVER] Client Closed Session\n")
        	}

			case msg_login @ Login(m) => {

				if (m == "pqrst") {

					println("\n[SERVER] PIN was Correct, waiting for Client transactions....\n")
					val success_ans = msg_login.cont !! Success()_


					success_ans ? {
						case msg_deposit @ Deposit(v) => {
							println("\n[SERVER] Deposit from Client accomplished....\n")
							val balance_ans 	= msg_deposit.cont !! Balance(v)_

							serverRecursiveHandler( balance_ans )
						}

						case msg_withdraw @ Withdraw(v) => {

							//Very simple Check on the ammount of the Withdraw
							if (v > 1200) {
								println("\n[SERVER] Client inserts an amount greater than his current money ammount....\n")
								val ans_withdraw = msg_withdraw.cont !! OverDraft()_

								serverRecursiveHandler( ans_withdraw )

							}else{

								println("\n[SERVER] Withdraw from Accomplished....\n")
								val ans_withdraw = msg_withdraw.cont !! Dispense()_

								serverRecursiveHandler( ans_withdraw )
							}

						}

						case Exit() => {
							println("\n[SERVER] Client closed Session....\n")
						}

					}

				}else{
					println("\n[SERVER] PIN was wrong, reloading Protocol....\n")

					//Gestione Caso PIN Errato
					val failure_ans = msg_login.cont !! Failure()_
					serverRecursiveHandler( failure_ans )
				}

			}
		}

	}
        
}


//Codice Cliente
object Client {

	def apply(channel_end: Out[ClientChoice]) (implicit timeout: Duration): Unit = clientRecursiveHandler(channel_end)
  
  	def clientRecursiveHandler (channel_end: Out[ClientChoice]) (implicit timeout: Duration) : Unit = {

		//Tentativo Login Cliente
    	val pin:String  		= "pqrst"
    	val login_ans         	= channel_end !! Login(pin)_
		println("\n[CLIENT] Invio PIN al Server.... ")


		//Attesa risposta Server
    	login_ans ? {

      		case msg_fail @ Failure() => {
          		println("\n[CLIENT] Il PIN inviato non è corretto, riprova \n")

				clientRecursiveHandler( msg_fail.cont )
        	}


			case msg_succ @ Success() => {
				val dp:Integer	     = 40
				println (s"\n[CLIENT] Tentativo Deposito di importo: ${dp}")


				//Client Transaction 1
				val deposit_response = msg_succ.cont !! Deposit(dp)_
				val bl				 = deposit_response.receive

				println (s"[CLIENT] Il deposito è stato portano a compimento \n")


				//Tentativo Login Cliente
				println("\n[CLIENT] Secondo Login con PIN al Server.... ")
    			val second_login         	= bl.cont !! Login(pin)_

				second_login ? {

					case msg_fail @ Failure() => {
          				println("\n[CLIENT] Il PIN inviato non è corretto, riprova \n")
						clientRecursiveHandler( msg_fail.cont )
        			}


					case msg_succ @ Success() => {

						//Client Transaction 2
						val vl:Integer			= 4000
						println(s"\n[CLIENT] Tentativo prelievo di ${vl}")
						val withdr = msg_succ.cont !! Withdraw(vl)_


						withdr ? {
							case m @ Dispense() => {
								println("[CLIENT] Il tuo prelievo è stato accetato dalla Banca\n")

								//Quitting Session
								println("\n[CLIENT] Chiudo sessione...")
								m.cont ! Quit()
							}

							case m @ OverDraft() => {
								println("[CLIENT] Non hai sufficiente copertura per prelevare la somma richiesta\n")

								//Quitting Session
								println("\n[CLIENT] Chiudo sessione...")
								m.cont ! Quit()
							}

						}

					}

				}

				
			}

    	}
  	}
    
}


//Oggetto Main - Starting Point Programma
object Main extends App {

	//Pulizia Contesto di Esecuzione
	def run() = main(Array())
	implicit val timeout = 5.seconds
  
	
	println("\n[!] Spawning local Server and Client...")
	println("_______________________________________________")
	val (server, client) = parallel[ClientChoice, Unit, Unit] (  ATM(_) , Client(_)   )


	//Aspetta la chiusura del Server
	Await.result(server , 10.seconds) 
	
}