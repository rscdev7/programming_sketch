import java.util.*;
import java.lang.*;
import java.net.*;
import java.io.*;
import java.util.Calendar;

public class Server{
	private static LinkedList<InetAddress> lista;
	public static void main (String argv []){
	
		lista=new LinkedList<InetAddress> ();	
		Calendar cal = Calendar.getInstance();
		int server_port=3233;

		try{
			ServerSocket s_socket=new ServerSocket (server_port);
			
			while (true) {
				System.out.println ("In attesa di richieste...");
				Socket rem_s=s_socket.accept();
				
				System.out.println ("Nuova connessione"+rem_s.getInetAddress());

				//Stream x Leggere
				InputStreamReader inp=new InputStreamReader (rem_s.getInputStream());
				BufferedReader in=new BufferedReader (inp);	
				
				//Stream x Scrivere
				OutputStreamWriter out=new OutputStreamWriter (rem_s.getOutputStream());
				PrintWriter ou=new PrintWriter (out,true);

				/*InputStreamReader isr = new InputStreamReader(rem_s.getInputStream());
                		BufferedReader in = new BufferedReader(isr);
                 
                		// Connect to output stream
               			OutputStreamWriter osw = new OutputStreamWriter(rem_s.getOutputStream());
               			PrintWriter out = new PrintWriter(osw, true);*/

				String query=in.readLine();

				System.out.println ("Ricevuto dak client "+query);
				
				if (query.equals ("TIME")==false) {
					System.out.println ("Time false ");
					ou.println ("Richiesta mal posta, retry");
					continue;
				} 	
				
				System.out.println ("Oltre ");
				InetAddress ind=rem_s.getInetAddress();

				if ((lista.contains(ind))==false) {
					int ora=cal.get(Calendar.HOUR);
					System.out.println ("Ora "+ora);
					String str="";
					str=String.valueOf(ora);
					ou.println(str);
					lista.add(rem_s.getInetAddress());
				}else{
					ou.println ("BANNED");	
				}	
				rem_s.close();
						
			}	
		}catch (Exception e){
			System.out.println ("Errore nella creazione della socket");
			return;
		}
	}

}
