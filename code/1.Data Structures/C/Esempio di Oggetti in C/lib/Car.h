struct Car{
    int height;
    int width;
    int res;
    void (*somma) (struct Car* car);
    void (*print) (struct Car* car);
};

//Metodo di somma 
void somma (struct Car* cs) {
    cs->res = cs->width + cs->height;
}

//Metodo di stampa
void print (struct Car* car) {
    printf ("Car Width: %d \n",car->width);
    printf ("Car Height: %d \n",car->height);
    printf ("Res: %d \n",car->res);
}

//Costruttore
void initCar (struct Car* pC, int pWidth, int pHeight) {
    pC->width = pWidth;
    pC->height = pHeight;
    pC->somma = somma;
    pC->print = print;
    pC->res   = -1;
}




