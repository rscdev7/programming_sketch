import java.net.*;
import java.io.*;
import java.util.*;

public class Client{
	public static void main (String argv []) {
		try{
			InputStreamReader ln=new InputStreamReader (System.in);
			BufferedReader console=new BufferedReader(ln);

			InetAddress inet=InetAddress.getByName ("127.0.0.1");
			Socket socket = new Socket(inet, 3333);
			
			//Creazione Stream di Ricezione
			InputStreamReader isr = new InputStreamReader(socket.getInputStream());
			BufferedReader in = new BufferedReader(isr);
			
	 		//Creazione Stream di Invio
			OutputStreamWriter osw = new OutputStreamWriter(socket.getOutputStream());
			PrintWriter out = new PrintWriter(osw, true);

			//Input da Tastiera
			System.out.println ("Inserisci una serie tv, e un episodio separati da virgola ");
			String str=console.readLine();

			//Invio richiesta al Server
			out.println (str);

			//Prelievo risposta
			String risposta=in.readLine();

			System.out.println ("Risposta Server: "+rispost);

			socket.close();
			
		}catch (IOException e) {
			System.out.println ("Errore \n");
			return;
		}
	}


}
