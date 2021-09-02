/*

Il componente CannyEdgeDetector permette di applicare l'Algoritmo di Canny ad una data immagine.

*/

#define GENERIC_ERROR -7
#define NOT_ALLOCATED_OBJECT -8
#define GRAY_SCALE_IMAGE_PROVIDED -9
#define TRUE 1
#define FALSE 0
#define M_PI 3.14159265358979323846
#include "../lib/ImageManipulator.h"
#include <string.h>

struct CannyEdgeDetector {
    struct ImageManipulator* _img;

    int (*toGrayScale) (struct CannyEdgeDetector* this);
};


/*PUBLIC*/
/*STATIC*/
unsigned char*** padImage (unsigned char*** pImg, int pWidth, int pHeight, int pChannels, int pKernelSize) {    

    //Calcolo la dimensione del pad e le relative dimensione dell'immagine paddata
    int pad       = (int) ( (pKernelSize - 1) / 2 );
    int padWidth  = pWidth  + ( 2   *   pad);
    int padHeight = pHeight + ( 2   *   pad);


    //Alloco un vettore di puntatori doppi pari al numero di canali dell'immagine
    unsigned char*** paddedImage = allocShapedImage(padWidth, padHeight, pChannels);
    fillZero(paddedImage,padWidth,padHeight,pChannels);


    //SCRIVO I DATI
    for (int i=0; i < pChannels; i++) {
        for (int j=0; j < pHeight; j++) {
            for (int k=0; k < pWidth; k++) {
                paddedImage[i][j+pad][k+pad] = (uint8_t)(pImg[i][j][k]);
            }
        }
    }

    free(pImg);
    return paddedImage;
}


/*PUBLIC*/
/*STATIC*/
unsigned char*** convolution (unsigned char*** pImg, int pWidth, int pHeight, double** pKernel, int pKernelSize, int pAverage) {

    int pad       = (int) ( (pKernelSize - 1) / 2 );

    unsigned char*** convolvedImage = allocShapedImage(pWidth, pHeight, 1);

    unsigned char*** originalImage = pImg;

    for (int i= 0; i < (pHeight); i++) {
        for (int j=0; j < (pWidth);j++) {

            if ( i >= (0 + pad) && i < (pHeight-pad)  && 
                 j >= (0 + pad) && j < (pWidth-pad) ) {
                    uint8_t sum = 0;

                    for (int z=0; z < (pKernelSize);z++) {
                        int startH = (i-pad) + z;
                        int startW = j-pad;

                        for (int k=0; k < (pKernelSize); k++) {
                            sum +=  ( pKernel[z][k] * ( (uint8_t) (originalImage[0][startH][startW+k]) ) );
                        } 

                    }

                    convolvedImage[0][i][j] = sum;

                    if (pAverage == TRUE) {
                        convolvedImage[0][i][j]/=(pKernelSize*pKernelSize);
                    }
           }else{
               convolvedImage[0][i][j] = 0;
           }

        }
    }

    free(pImg);
    return convolvedImage;
}


/*PUBLIC*/
/*STATIC*/
//Questa funzione restituisce la suddivisione dell'intervallo [pStar , pEnd] in pDensity parti.
double* linspace (double pStart, double pEnd, int pDensity) {
    if (pDensity==0) return NULL;

    double* linArray = (double*) malloc (pDensity * sizeof(double));

    if (pDensity == 1) {
        linArray[0] = pStart;
        return linArray;
    }

    double delta = (pEnd - pStart)  / (pDensity - 1);

    for (int i = 0; i < (pDensity-1); i++) {
        linArray[i] = ( pStart + (delta * i) );
    }

    linArray[pDensity-1] = pEnd;

    return linArray;
}


/*PUBLIC*/
/*STATIC*/
//Questa funzione calcola la Gaussiana Univariata 
double dNorm (float pX, float pMean, float pDevST) {
    return 1 / (sqrt(2 * M_PI) * pDevST) * exp(-pow((pX - pMean) / pDevST, 2) / 2);
}


/*PRIVATE*/
//Questa funzione costruisce la versione 2D del kernel 1D passato in input
double** make2DKer (double* pData, int pSize) {
    double** kernel2D = (double**) malloc (pSize*sizeof(double*));

    for (int i=0; i< pSize; i++) {
        kernel2D[i] = (double*) malloc (pSize * sizeof(double)); 
    }

    for (int i=0; i< pSize; i++) {
        for (int j=0; j< pSize; j++) {
            kernel2D[i] [j] = pData[i] * pData[j];
        }
    }

    return kernel2D;
}


/*STATIC*/
/*PUBLIC*/
//Questa funzione costruisce il kernel Gaussiano atto allo smoothing dell'immagine
double** buildGaussianKernel (int pSize, float pDevst) {
    int startKernel = (int) (- (pSize/2) );
    int endKernel   = (int) (pSize / 2);
    int densityKernel = pSize;

    double* kernel1D = linspace (startKernel, endKernel, densityKernel);

    for (int i=0; i < pSize; i++) {
        kernel1D[i] = dNorm(kernel1D[i], 0 , pDevst);
    }

    double** kernel2D = make2DKer(kernel1D,pSize);

    double maxKer = 0;
    
    for (int i=0; i< pSize; i++) {
        for (int j=0; j< pSize; j++) {
            if (kernel2D[i][j] > maxKer) {
                maxKer = kernel2D[i][j];
            }
        }
    }

    for (int i=0; i< pSize; i++) {
        for (int j=0; j< pSize; j++) {
            kernel2D[i][j] = kernel2D[i][j]*(1.0/maxKer);
        }
    }

    return kernel2D;
}


/*PUBLIC*/
//Questa funzione converte un'immagine a colori in un'immagine a scala di grigi facendo una media artimetica dei valori dei tre canali
int toGrayScale (struct CannyEdgeDetector* this) {
    if (this == NULL) return NOT_ALLOCATED_OBJECT;

    if (this->_img->_loadedChannels != 3 && this->_img->_loadedChannels != 4) {
        return GRAY_SCALE_IMAGE_PROVIDED;
    }

    if (this->_img->_shapedImage != NULL) {
        this->_img->_image = flatten(this->_img->_shapedImage, this->_img->_width, this->_img->_height, this->_img->_loadedChannels);
        this->_img->_shapedImage = NULL;
    }

    unsigned char* grayScaleImage = allocLinearImage(this->_img->_width, this->_img->_height, 1);

    int counter = 0;
    for (int i=0; i < (this->_img->_width * this->_img->_height); i++) {
        int mean = ( this->_img->_image[counter] + this->_img->_image[counter+1] + this->_img->_image[counter+2] )/ (3);
        grayScaleImage[i] = mean;

        counter+=3;
    }

    free(this->_img->_image);
    this->_img->_image = grayScaleImage;
    this->_img->_loadedChannels = 1;

    return SUCCES;
}


/*PUBLIC*/
//Inizializzatore del componente
void initCanny (struct CannyEdgeDetector* this, struct ImageManipulator* pIMg) {
    this->_img                  = pIMg;
    this->toGrayScale           = toGrayScale;
}
