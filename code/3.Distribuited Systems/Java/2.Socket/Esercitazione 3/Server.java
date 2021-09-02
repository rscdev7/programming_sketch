import java.util.*;
import java.lang.*;
import java.net.*;
import java.io.*;

public class Server{

	private static HashMap<String,Integer> mappa;
	public static void inizio () {
		mappa.put ("Il Trono di Spade",10);
		mappa.put ("Libro Cuore",30);
		mappa.put ("Cormen",15);
		mappa.put ("Tanenbaum",50);
	}

	public static void main (String argv[]) {
		mappa=new HashMap<String,Integer> ();
		inizio();
		try{
			ServerSocket s=new ServerSocket (3333);	
			while (true) {
				System.out.println ("In attesa di connessioni.......");
				Socket rem=s.accept();
				System.out.println ("Client connesso");
				
				//Creazione Buffer Ricezione
				InputStreamReader i=new InputStreamReader (rem.getInputStream());
				BufferedReader in=new BufferedReader (i);
	
				//Creazione Buffer Invio
				OutputStreamWriter ou=new OutputStreamWriter (rem.getOutputStream());
				PrintWriter out=new PrintWriter (ou,true);

				String risp=in.readLine();
				boolean ex=false;
				try{
					StringTokenizer st=new StringTokenizer (risp,",");
					String titolo=st.nextToken(",");
					String copie=st.nextToken(",");
					if (mappa.containsKey (titolo)==true) {
						int val=mappa.get (titolo);
						int op=Integer.parseInt(copie);
						if (op<=val) {
							out.println ("true");
						}else{
							out.println ("false");
						}
					}else{
						out.println ("false");
					}
				}catch (NoSuchElementException e) {
					ex=true;
				}
				if (ex==true) out.println ("Richiesta mal formata");
				rem.close();
			}
		}catch(IOException e) {
			System.out.println ("Errore creazione socket");
			return;
		}
	}


}
