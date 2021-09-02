/*

Questo modulo permette di testare il funzionamento del componente CannyEdgeDetector.

*/
#include <stdio.h>
#include <stdlib.h>
#include "../lib/CannyEdgeDetector.h"

int main (int argc, char** argv) {

    //Caricamento immagine da disco
    struct ImageManipulator img;
    initImageManipulator(&img,"../data/lena.png",3);
    //initImageManipulator(&img,"../data/sky.jpg",3);


    //Allocazione componente CannyEdgeDetector
    struct CannyEdgeDetector cn;
    initCanny(&cn,&img);


    //Test trasformazione e salvataggio immagine in scala di grigi su disco
    int ris = cn.toGrayScale(&cn);
    if (ris == SUCCES) {
        printf ("\nConversione in scala di grigi effettuata correttamente \n");
    }else{
        printf ("\nErrore nella conversione a scala di grigi \n");
        exit(GENERIC_ERROR);
    }
    
    char filename[100] = "../data/gray_scale_lena";
    //char filename[100] = "../data/gray_scale_sky";
    cn._img->write(cn._img, filename);

    
    //Test funzione di linspace
    double low = 6;
    double high = 23.4;
    int density = 5;
    double* ptr = linspace(low, high, density);

    printf ("\n Linspace (start = %f , end = %f , density = %d) \n",low,high,density);
    printf ("\t[ ");
    for (int i=0;i<density;i++) {
        if (i == (density-1)) {
            printf ("%f ]\n\n",ptr[i]);\
        }else{
            printf ("%f , ",ptr[i]);
        }
    }


    //Test funzione Gaussiana
    float x     = 1.0;
    float mean  = 0.0;
    float devSt = 0.25;
    printf ("\n Calcolo Gaussiana d'esempio: \n     1) x = %f \n     2) Media = %f \n     3) Deviazione Standard = %f \n     4) G(%f) = %f \n\n",x,mean,devSt,x,dNorm(1,0,0.25));


    //Stampa Kernel Gaussiano
    int size = 15;
    double** ker = buildGaussianKernel(size,sqrt(size));
    printf ("\n Kernel Gaussiano %dx%d \n",size,size);
    for (int i=0; i< size; i++) {
        
        printf ("| ");
        for (int j=0; j<size;j++) {
            if (j== (size-1)) {
                printf (" %f |",ker[i][j]);
            }else{
                printf (" %f ,",ker[i][j]);
            }
        }
        printf ("\n");
    }
    printf ("\n");


    //Padding dell'immagine
    cn._img->shapeImage(cn._img);

    int pad       = (int) ( (size - 1) / 2 );
    int padWidth  = cn._img->_width + (2*pad);
    int padHeight = cn._img->_height + (2* pad);

    cn._img->_shapedImage = padImage(cn._img->_shapedImage, cn._img->_width, cn._img->_height, cn._img->_loadedChannels, size);


    cn._img->_width  = padWidth;
    cn._img->_height = padHeight;

    char padImg[100] = "../data/paddedImageLena";
    //char padImg[100] = "../data/paddedImageSky";
    cn._img->write(cn._img,padImg);


    //Convoluzione col kernel Gaussiano
    /*cn._img->shapeImage = convolution(cn._img->_shapedImage,cn._img->_width, cn._img->_height, ker, size, FALSE);

    char convImg[100] = "../data/convImg";
    cn._img->write(cn._img,convImg);*/

    

}