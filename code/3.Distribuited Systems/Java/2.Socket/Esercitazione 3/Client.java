import java.util.*;
import java.lang.*;
import java.net.*;
import java.io.*;

public class Client{
	public static void main (String argv[]) {
		try{
			InetAddress addr=InetAddress.getByName ("127.0.0.1");
			Socket rem=new Socket (addr,3333);

			InputStreamReader con=new InputStreamReader (System.in);
			BufferedReader console=new BufferedReader (con);
	
			InputStreamReader i=new InputStreamReader (rem.getInputStream());
			BufferedReader in=new BufferedReader (i);

			OutputStreamWriter ou=new OutputStreamWriter (rem.getOutputStream());
			PrintWriter out=new PrintWriter (ou,true);

			System.out.println ("Inserisci un libro e una seria separati da virgola");
			String input=console.readLine ();

			out.println (input);

			String risp=in.readLine();

			System.out.println ("Risposta server: "+risp);			

			rem.close();
		

		}catch(IOException e) {
			System.out.println ("Errore apertura socket ");
			return;
		}
	}

}

