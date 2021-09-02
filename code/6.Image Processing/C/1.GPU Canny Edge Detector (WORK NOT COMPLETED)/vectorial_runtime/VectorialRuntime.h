#include <stdio.h>
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

struct Device{
    cl_device_id device_id;
    char* name;
};

struct Platform  {
    cl_platform_id platform_id;
    char* name;
    int num;
    struct Device* deviceList;
};

struct VectorialRuntime{
    struct Platform* _platformList;
};

void scanDevices (struct VectorialRuntime* this) {
    cl_uint nplats;
	cl_int err;
    cl_platform_id* ids;

	err = clGetPlatformIDs(0, NULL, &nplats);
	ocl_check(err, "Conteggio piattaforem");

    this->_platformList = (struct Platform*)(malloc(nplats*sizeof(struct Platform))); 
    this->_platformList->num = nplats;

	err = clGetPlatformIDs(this->_platformList->num, ids, NULL);
	ocl_check(err, "getting platform IDs");
    /*
    cl_uint ndevs;
	cl_device_id *devs;

    int i=0;

    if (nplats==0) {
        printf ("\nErrore, Nessuna Piattaforma di Calcolo Parallelo Trovata sul Sistema !");
        printf("\n\nPossibili cause: \n 1) Nessun device di calcolo parallelo installato sulla macchina \n 2) Mancata installazione del driver per il device di calcolo \n 3) Mancata installazione degli Header/ICD OpenCL \n");
        exit(2);
    }
    
    printf("\n");

    for (i=0;i<nplats;i++) {

        char buffer[BUFSIZE];

	    err = clGetPlatformInfo(plats[i], CL_PLATFORM_NAME, BUFSIZE,
		buffer, NULL);
	    ocl_check(err, "getting platform name");

        printf("Piattaforma %d: %s \n", i+1, buffer);

        char dev[BUFSIZE];

        err = clGetDeviceIDs(plats[i], CL_DEVICE_TYPE_ALL, 0, NULL, &ndevs);
	    ocl_check(err, "counting devices");

        devs = malloc(ndevs*sizeof(*devs));

        err = clGetDeviceIDs(plats[i], CL_DEVICE_TYPE_ALL, ndevs, devs, NULL);
	    ocl_check(err, "devices #2");

        if (ndevs == 0) {
            printf ("\n");
        }
        for (int j=0;j<ndevs;j++) {
            
            err = clGetDeviceInfo(devs[j], CL_DEVICE_NAME, BUFSIZE,
		dev, NULL);
	        ocl_check(err, "device name");

            printf("\t Device %d: %s \n", j+1, dev);
        }

        printf ("\n");
        
    }

    printf ("\n");
    */
}
