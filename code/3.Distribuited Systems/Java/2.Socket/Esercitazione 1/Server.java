import java.net.*;
import java.io.*;
import java.util.*;

public class Server {
	private static ShowList data=new ShowList ();

	public static void printSocketInfo(Socket socket) {
        	System.out.println("Local Address: " + socket.getLocalAddress());
       	 	System.out.println("Local Port: " + socket.getLocalPort());
       		System.out.println("Remote Address: " + socket.getInetAddress());
       		System.out.println("Remote Port: " + socket.getPort());
	}

	public static void main (String argv []) {
		try{
			ServerSocket serverSocket = new ServerSocket(3333);

			while (true) {
				System.out.println ("In attesa di richieste... \n");

				Socket clientStream = serverSocket.accept();

				printSocketInfo(clientStream);

				//Creazione Stream per Leggere
				InputStreamReader a=new InputStreamReader(clientStream.getInputStream());
				BufferedReader c=new BufferedReader (a);
				
				//Creazione Stream per scrivere
				OutputStreamWriter out=new OutputStreamWriter (clientStream.getOutputStream());
				PrintWriter wr=new PrintWriter (out,true);
				
				String query=c.readLine();
				System.out.println ("Ricevuto un dato "+query);

				try{
					//PARSING STRINGA
					StringTokenizer token=new StringTokenizer(query,",");

					//CONTROLLO STRUTTURA STRINGA	
					if (token.countTokens()==2) {
							String serie=token.nextToken();
							String n_ep=token.nextToken();

							try{		
								int n=Integer.parseInt (n_ep,10);
								
								int ris=data.isAvaible (serie,n);

								switch (ris) {
									case (0): wr.println ("La serie e l'episodio richiesta sono assente");
										  break;
									case (1): wr.println ("La serie e l'episodio richiesti sono presenti");
										  break;
									case(2):  wr.println ("La serie e' presente, l'episodio e' assente");
										  break;  		
								}

							}catch (NumberFormatException e) {
								wr.println ("Richiesta mal posta, riprovare");		
							}
					}else{
						wr.println ("Richiesta mal posta, riprovare");
					}

				}catch (NullPointerException e) {
					wr.println ("Richiesta mal posta, riprovare");
				}
				clientStream.close();
			}
			
		}catch (IOException e) {
			System.out.println ("Errore nella creazione della socket \n");
			return;
		}
	}
}
