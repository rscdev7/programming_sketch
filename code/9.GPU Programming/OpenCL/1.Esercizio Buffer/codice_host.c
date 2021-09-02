#define CL_TARGET_OPENCL_VERSION 120
#include "ocl_boiler.h"
#include <stdio.h>
#include <stdlib.h>

//Variabile che contiene il valore del Warp size preferito dall'hardware
size_t vecinit_wg_preferred;

//Funzione d'errore per le chiamate openCL
void error(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

int main (int argc, char *argv[]) {

	//Variabili
	cl_int err;
	cl_event evt_read;

	//Controllo Parametri in input
	if (argc != 2) {
		error("errore numero argomenti: ");
	}

	//Prelievo dimensione vettore
	const int numels=atoi(argv[1]);
	const size_t memsize = /*numels*sizeof(int)*/ 1*sizeof(int);
	cl_int* h_vsum = malloc(memsize);

	//Scelta Device e Compilazione Programma Device
	cl_platform_id p = select_platform();
	cl_device_id d = select_device(p);
	cl_context ctx = create_context(p, d);
	cl_command_queue que = create_queue(ctx, d);
	cl_program prog = create_program("codice_device.ocl", ctx, d);

	//Creazione kernel
	cl_kernel kernel_k = clCreateKernel(prog, "nome_kernel", &err);
	ocl_check(err, "create kernel");

	/* Allocazione buffer */
	cl_mem d_v1 = clCreateBuffer(ctx, CL_MEM_READ_WRITE, 1*sizeof(int), NULL, &err);
	ocl_check(err, "create buffer v1");

	//Attendo che venga eseguita tutta la coda di comandi
	err = clFinish(que);
	ocl_check(err, "clFinish");

	cl_int* vs= malloc (1*sizeof(int));
	/*for (int i=0;i<1;i++) {
		vs[i]=5;
	}*/
	vs[0]=0;
	//Inserisco una lettura nella coda di comandi
	err = clEnqueueWriteBuffer(que, d_v1,
			CL_TRUE, 0, 1*sizeof(int),
			vs,
			0, NULL, &evt_read);
	ocl_check(err, "read buffer vsum");

	//Aspetto che la lettura sia finita
	err = clFinish(que);
	ocl_check(err, "clFinish");

	//Inserisco una lettura nella coda di comandi
	err = clEnqueueReadBuffer(que, d_v1,
			CL_TRUE, 0, 1*sizeof(int),
			h_vsum,
			0, NULL, &evt_read);
	ocl_check(err, "read buffer vsum");

	//Aspetto che la lettura sia finita
	err = clFinish(que);
	ocl_check(err, "clFinish");

	//Stampo il vettore con i nuovi valori
	for (int i=0;i<1;i++) {
		printf ("Posizione %d - Elemento %d \n",i,h_vsum[i]);
	}

	//Rilascio le risorse allocate
	clReleaseContext(ctx);
	clReleaseCommandQueue(que);
	clReleaseProgram(prog);
	clReleaseKernel(kernel_k);
	clReleaseMemObject(d_v1);
	free(h_vsum);

	//Uscita dal programma
	return 0;

}
