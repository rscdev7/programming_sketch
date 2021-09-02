import java.lang.*;
import java.util.*;

public class ShowList {
	private static HashMap<String,Integer> mappa;
	public ShowList () {
		mappa=new HashMap<String,Integer>();
		mappa.put ("House of Karts",5);
		mappa.put ("Strange Things",10);
		mappa.put ("Baking Brad",12);
		mappa.put ("Marcos",5);
		mappa.put ("Black Mails",15);
		mappa.put ("Rick e morto",4);
	}
	int isAvaible (String nome_serie,int n_episodi) {
		boolean av=mappa.containsKey(nome_serie);
		if (av==true) {
			int n_ep=mappa.get(nome_serie);
			if (n_ep>=n_episodi) return 1;  //Serie Presente
			return 2; //Serie Presente, ma l'episodio no
		}
		return 0; //Serie Assente
	}

}
