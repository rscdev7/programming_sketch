import java.util.*;
import java.lang.*;
import java.net.*;
import java.io.*;

public class Client{
	public static void main (String argv[]) {

		try{
			InetAddress addr=InetAddress.getByName ("127.0.0.1");

			while (true) {
				Socket a=new Socket (addr,3233);

				InputStreamReader con=new InputStreamReader (System.in);
				BufferedReader console=new BufferedReader (con);

           			InputStreamReader isr = new InputStreamReader(a.getInputStream());
            			BufferedReader in = new BufferedReader(isr);
             
            			OutputStreamWriter osw = new OutputStreamWriter(a.getOutputStream());
            			PrintWriter out = new PrintWriter(osw, true);

				System.out.println ("Invia una richiesta: ");

				String query=console.readLine();
	
				out.println (query);

				String risposta=in.readLine();

				System.out.println ("Risposta Server: "+risposta);
				a.close();
						
			}
		}catch(IOException e) {
			System.out.println ("Errore apertura socket");
		}
	}
}
