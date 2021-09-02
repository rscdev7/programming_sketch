/*
Si riesce a simulare abbastanza bene gli oggetti C++, gli unici deficit sono:

1) Ereditarietà molto più dispendiosa: Bisogna risalire la gerarchia ereditaria manualmente oppure creare dei Wrapper (che hanno nomi diversi) alle funzioni della classe Base (tutto questo lungo tutta la gerarchia ereditaria).
2) Modificatori di accesso inrealizzabili.
3) Ogni chiamata a funzione che modifica lo stato dell'oggetto deve avere passato come parametro l'indirizzo dell'oggetto stesso.

*/

#include <stdio.h>
#include <stdlib.h>
#include "./lib/SuperCar.h"

int main (int argc, char** argv) {

    //Dichiarazione "Oggetto"
    struct Car a;

    //"Costruttore"
    initCar(&a,400,300);

    //Esecuzione "Metodo Somma"
    a.somma(&a);

    //Stampa "membri della classe"
    printf ("\n CAR \n");
    a.print(&a);



    //Dichiarazione "Oggetto"
    struct SuperCar k;

    //"Costruttore"
    initSuperCar(&k,3000,8);

    //Stampa "membri della classe Base" risalendo la gerarchia ereditaria
    printf ("\n SUPER CAR - RISALITA ALBERO EREDITARIO \n");
    k.ts.print(&k.ts);

    //Stampa "membri della classe Base" utilizzando il Wrapper alla funzione della classe base
    printf ("\n SUPER CAR - WRAPPER \n");
    k.newPrint(&k);

    //Stampa "membri della classe"
    printf ("\n SUPER CAR - PARAMETRI DELLA CLASSE \n");
    k.printSc(&k);
    
}