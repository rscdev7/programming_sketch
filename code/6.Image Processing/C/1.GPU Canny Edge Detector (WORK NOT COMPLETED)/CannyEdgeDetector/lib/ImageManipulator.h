/*

Il componente ImageManipulator permette di leggere e scrivere su/di un'immagine jpg/png.

*/

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#define EMPTY_VALUE                 -1
#define ERROR_IMAGE_READ            -2
#define OUT_OF_RANGE_VALUE          -3
#define ERROR_IMAGE_WRITE           -4
#define NOT_ALLOC_SHAPED_IMAGE      -5
#define UNKNOWN_IMAGE_FORMAT        -6
#define NOT_ALLOC_FLAT_IMAGE        -7
#define SUCCES                       0
#define COMPRESSION_QUALITY          100

struct ImageManipulator{
    char*                 _path;
    unsigned char*        _image;
    unsigned char***      _shapedImage;
    int                   _width;
    int                   _height;
    int                   _loadedChannels;


    void            (*printInfo)      (struct ImageManipulator* this);
    int             (*write)          (struct ImageManipulator* this, char* pWrPath);
    void            (*resetData)      (struct ImageManipulator* this);
    int             (*shapeImage)     (struct ImageManipulator* this);
};


/*STATIC*/
/*PUBLIC*/
//Alloca un'immagine con indicizzazione sequenziale
unsigned char* allocLinearImage (int pWidth, int pHeight, int pChannels) {
    unsigned char* linImage = (unsigned char*)malloc ((pWidth*pHeight*pChannels)*sizeof(unsigned char));

    return linImage;
}


/*STATIC */
/*PUBLIC*/
//Alloca un'immagine con indicizzazione a n-uple
unsigned char*** allocShapedImage (int pWidth, int pHeight, int pChannels) {

    //Alloco un vettore di puntatori doppi pari al numero di canali dell'immagine
    unsigned char*** im = (unsigned char***) malloc(pChannels * sizeof(unsigned char **));

    //Per ogni canale, alloco un array di puntatori grande quanto l'altezza dell'immmagine
    for (int i=0; i < pChannels; i++) {
        im[i] = (unsigned char**) malloc (pHeight * sizeof (unsigned char*));
    }

    //Per ogni elemento ,di ogni canale, dell'altezza dell'immagine: alloco un array di unsigned char grande quanto la larghezza dell'immagine
    for (int i=0; i< pChannels; i++) {
        for (int j=0; j < pHeight;j++) {
            im[i][j] = (unsigned char*) malloc(pWidth * sizeof(unsigned char));
        }
    }

    return im;
}


/*STATIC */
/*PUBLIC*/
//Colora di nero l'immagine in input
void fillZero (unsigned char*** pImg, int pWidth, int pHeight, int pChannels) {
    for (int k=0;k< pChannels;k++) {
       for (int i=0;i< pHeight;i++) {
           for (int j=0;j< pWidth;j++) {
               pImg[k][i][j] = (uint8_t)0;
            }
        } 
    }
}


/*STATIC */
/*PUBLIC*/
//Linearizza l'immagine passata in input
unsigned char* flatten (unsigned char*** pImgShaped, int pWidth, int pHeight, int pChannels){
    if (pImgShaped == NULL) {
        return NULL;
    }

    unsigned char* im = allocLinearImage(pWidth,pHeight,pChannels);
    
    int counter = 0;
    for (int i=0; i< pHeight; i++) {
        for (int j=0; j < pWidth; j++) {
            for (int k=0; k < pChannels; k++) {
                im[counter] = pImgShaped[k][i][j];
                counter++;
            }
        }
    }

    free(pImgShaped);

    return im;
}


/*PRIVATE*/
//La funzione writeImageJpg permette di salvare un'immagine in jpg utilizzando un parametro di qualità che va da 1 (massima compressione/minima qualità) a 100 (minima compressione/massima qualità)
int writeImageJpg (struct ImageManipulator* this, char* pWrPath) {

    if (this->_shapedImage != NULL) {
        this->_image = flatten(this->_shapedImage, this->_width, this->_height, this->_loadedChannels);

        this->_shapedImage = NULL;
    }
    
    int res = stbi_write_jpg(pWrPath, this->_width, this->_height, this->_loadedChannels, this->_image, COMPRESSION_QUALITY);
    
    if (res != 1) {
        return ERROR_IMAGE_WRITE;
    }else{
        return SUCCES;
    }
}


/*PRIVATE*/
//La funzione writeImagePng permette di salvare un'immagine in png
int writeImagePng (struct ImageManipulator* this, char* pWrPath) {
    if (this->_shapedImage != NULL) {
        this->_image = flatten(this->_shapedImage, this->_width, this->_height, this->_loadedChannels);

        this->_shapedImage = NULL;
    }

    int res = stbi_write_png(pWrPath, this->_width, this->_height, this->_loadedChannels, this->_image, this->_width * this->_loadedChannels);
    
    if (res != 1) {
        return ERROR_IMAGE_WRITE;
    }else{
        return SUCCES;
    }
}


/*PUBLIC*/
//La procedura printInfo stampa le caratteristiche salienti dell'immagine caricata
void printInfo (struct ImageManipulator* this) {
    printf ("**********IMAGE INFO********** \n\n");
    printf ("-> Path Immagine: %s \n", this->_path);
    printf ("-> Larghezza Immagine: %d \n", this->_width);
    printf ("-> Altezza Immagine: %d \n", this->_height);
    printf ("-> Canali Immagine: %d \n\n", this->_loadedChannels);
    printf ("****************************** \n");
}


/*PUBLIC*/
//Scrive l'immagine su disco selezionando il formato opportuno
int write (struct ImageManipulator* this, char* pWrPath) {
    char* jpg = strstr (pWrPath, ".jpg");
    char* png = strstr (pWrPath, ".png");

    //Caso in cui viene specificata l'estensione
    if (jpg != NULL) {
        return writeImageJpg(this,pWrPath);
    }else if (png != NULL){
        return writeImagePng(this,pWrPath);
    }


    //Caso in cui non viene specificata l'estensione
    jpg = strstr (this->_path, ".jpg");
    png = strstr (this->_path, ".png");

    if (jpg != NULL) {
        strcat(pWrPath, ".jpg");
        return writeImageJpg(this,pWrPath);
    }else if (png != NULL){
        strcat(pWrPath, ".png");
        return writeImagePng(this,pWrPath);
    }

    return UNKNOWN_IMAGE_FORMAT;
}


/*PUBLIC*/
//La funzione resetData permette di svuotare la struttura 
void resetData (struct ImageManipulator* this ) {
    if (this->_image != NULL) {
        stbi_image_free(this->_image);
        this->_image = NULL;
    }
    
    this->_path            = NULL;

    this->_width           = EMPTY_VALUE;
    this->_height          = EMPTY_VALUE;
    this->_loadedChannels  = EMPTY_VALUE;
    
    free(this->_shapedImage);
    this->_shapedImage     = NULL;
}


/*PUBLIC*/
//Trasforma l'immagine lineare in un parallelepipedo
int shapeImage (struct ImageManipulator* this) {

    if (this->_image == NULL) {
        return NOT_ALLOC_FLAT_IMAGE;
    }

    this->_shapedImage = allocShapedImage(this->_width, this->_height, this->_loadedChannels);    

    //Scrivo i dati dall'immagine lineare
    int counter = 0;
    for (int i=0; i< this->_height; i++) {
        for (int j=0; j < this->_width;j++) {
            for (int k=0; k < this->_loadedChannels; k++) {
                this->_shapedImage[k][i][j] = this->_image[counter];
                counter++;
            }
        }
    }

    stbi_image_free(this->_image);
    this->_image = NULL;

    return SUCCES;
}


/*PUBLIC*/
//Inizializzatore del Componente
int initImageManipulator (struct ImageManipulator* this, char* pPath, int pChannelsToLoad){
    int channels;

    this->_path             = pPath;
    this->_loadedChannels   = pChannelsToLoad;
    this->_shapedImage      = NULL;
    
    this->_image = stbi_load(this->_path, &this->_width, &this->_height, &channels, this->_loadedChannels);

    if (this->_image == NULL) {
        return ERROR_IMAGE_READ;
    }

    this->printInfo          = printInfo;
    this->resetData          = resetData;
    this->shapeImage         = shapeImage;
    this->write              = write;

    return SUCCES;
}
