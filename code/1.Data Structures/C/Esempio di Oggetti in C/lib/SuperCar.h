#include "Car.h"

struct SuperCar{
    struct Car ts;
    int _cilindrata;
    int _numeroCilindri;
    void (*newPrint) (struct SuperCar* cs);
    void (*printSc) (struct SuperCar* cs);
};

//Wrapper ad un metodo della "classe base"
void newPrint (struct SuperCar* cs) {
    cs->ts.print(&cs->ts);
}

//Metodo di stampa per i membri di classse
void printSc (struct SuperCar* cs) {
    printf ("Cilindri: %d \n",cs->_numeroCilindri);
    printf ("Cilindrata: %d \n",cs->_cilindrata);
}

//Costruttore
void initSuperCar (struct SuperCar* cs, int cilindrata, int _numeroCilindri) {
    struct Car k;
    initCar(&k,400,300);
    cs->ts = k;

    cs->_cilindrata = cilindrata;
    cs->_numeroCilindri = _numeroCilindri;
    cs->newPrint = newPrint;
    cs->printSc = printSc;
}

