/*

Il seguente modulo permette di testare il funzionamento del componente ImageManipulator; nello specifico l'idea è di caricare un'immagine jpg da disco (caricando solo le componenti RGB) e di colorare di rosso la prima riga dell'immagine.

Un ulteriore obbiettivo del modulo è stampare le caratteristiche salienti dell'immagine caricata.

*/

#include <stdio.h>
#include <stdlib.h>
#include "../lib/ImageManipulator.h"
#define ARGS_ERROR -7

int main (int argc, char** argv) {

    //Controllo che l'utente passi i corretti parametri dalla shell
    if (argc !=3) {
        printf ("Errore, bisogna passare al programma i seguenti argomenti: \n 1) Path dell'Immagine da Caricare \n 2) Path di Scrittura per l'Immagine Modificata \n \n");

        exit(ARGS_ERROR);
    }


    //Carico l'immagine da disco scartando l'eventuale canale di trasparenza
    struct ImageManipulator img;
    int channelsToLoad = 3;
    int res= initImageManipulator(&img, argv[1], channelsToLoad);

    if (res == ERROR_IMAGE_READ) {
        printf ("Errore nella lettura dell'immagine, controllare di aver inserito un nome di file valido \n");
        
        exit(ERROR_IMAGE_READ);
    }else{
        printf ("\nImmagine letta correttamente da disco \n\n");
    }


    //Stampo le caratteristiche salienti dell'immagine
    img.printInfo(&img);
    

    //Coloro di rosso la prima metà della prima linea dell'immagine
    int counter = 0;
    for (int i=0;i<(img._width/2);i++) {
        img._image[counter] = (uint8_t)(255);
        counter++;

        img._image[counter] = (uint8_t)(0);
        counter++;

        img._image[counter] = (uint8_t)(0);
        counter++; 
    }


    img.shapeImage(&img);


    //Colora di nero un'immagine
    //fillZero(img._shapedImage, img._width, img._height, img._loadedChannels);

    
    //Coloro di rosso la prima metà della prima linea dell'immagine. [Versione con immagine shaped]
    /*for (int i=0;i<(img._width/2);i++) {
        img._shapedImage[0][0][i] = 255;
        img._shapedImage[1][0][i] = 0;
        img._shapedImage[2][0][i] = 0;
    }*/
    


    //Salvo l'immagine su disco con la massima qualità
    int ris = img.write(&img, argv[2]);
    
    if (ris == SUCCES) {
        printf ("\nImmagine Scritta Correttamente su Disco \n");
    }else{
        printf ("\nErrore nella scrittura dell'immagine \n");
    }


    //Reset del componente
    img.resetData(&img);

    if (img._image == NULL) {
        printf ("\nReset avvenuto con successo \n");
    }else{
        printf ("Errore nel reset del componente \n");
    }
    
}