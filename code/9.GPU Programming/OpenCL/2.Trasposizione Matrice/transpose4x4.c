#define CL_TARGET_OPENCL_VERSION 120
#include "ocl_boiler.h"

#include <stdio.h>
#include <stdlib.h>

void error(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

cl_event matinit(cl_command_queue que, cl_kernel matinit_k,
	cl_mem d_mat, cl_int nrows, cl_int ncols,
	int n_wait_events, cl_event *wait_events)
{
	cl_int err;
	cl_int arg = 0;
	err = clSetKernelArg(matinit_k, arg++, sizeof(d_mat), &d_mat);
	ocl_check(err, "set matinit arg %d", arg - 1);
	err = clSetKernelArg(matinit_k, arg++, sizeof(nrows), &nrows);
	ocl_check(err, "set matinit arg %d", arg - 1);
	err = clSetKernelArg(matinit_k, arg++, sizeof(ncols), &ncols);
	ocl_check(err, "set matinit arg %d", arg - 1);

	// scelta manuale del work-group size:
	// gws deve essere multiplo di lws in ogni direzione
	const size_t lws[] = { 32, 8 };
	const size_t gws[] = {
		round_mul_up(ncols/4, lws[0]),
		round_mul_up(nrows, lws[1]),
   	};
	printf ("Colonne arrotondate: %ld - Righe arrotondate: %ld \n",round_mul_up(ncols, lws[0]),round_mul_up(nrows, lws[1]));

	cl_event evt_init;
	err = clEnqueueNDRangeKernel(
		que, matinit_k,
		2, NULL, gws, lws,
		n_wait_events, wait_events, &evt_init);
	ocl_check(err, "enqueue matinit");

	return evt_init;
}

cl_event transpose(cl_command_queue que, cl_kernel trans_k,
	cl_mem d_in, cl_mem d_out,
	cl_int nrows, cl_int ncols, // dell'input
	int n_wait_events, cl_event *wait_events)
{
	cl_int err;
	cl_int arg = 0;
	err = clSetKernelArg(trans_k, arg++, sizeof(d_in), &d_in);
	ocl_check(err, "set trans arg %d", arg - 1);
	err = clSetKernelArg(trans_k, arg++, sizeof(d_out), &d_out);
	ocl_check(err, "set trans arg %d", arg - 1);
	err = clSetKernelArg(trans_k, arg++, sizeof(nrows), &nrows);
	ocl_check(err, "set trans arg %d", arg - 1);
	err = clSetKernelArg(trans_k, arg++, sizeof(ncols), &ncols);
	ocl_check(err, "set trans arg %d", arg - 1);

	// scelta manuale del work-group size:
	// gws deve essere multiplo di lws in ogni direzione
	const size_t lws[] = { 32, 8 };
	const size_t gws[] = {
		round_mul_up(ncols/4, lws[0]),
		round_mul_up(nrows, lws[1]),
   	};
	printf ("Colonne arrotondate: %ld - Righe arrotondate: %ld \n",round_mul_up(ncols/4, lws[0]),
	round_mul_up(nrows/4, lws[1]));

	cl_event evt_trans;
	err = clEnqueueNDRangeKernel(
		que, trans_k,
		2, NULL, gws, lws,
		n_wait_events, wait_events, &evt_trans);
	ocl_check(err, "enqueue trans");

	return evt_trans;
}

// verify sulla trasposta,
// nrows ed ncols sono della trasposta
void verify(const int *mat, int nrows, int ncols)
{
	for (int r = 0; r < nrows; ++r) {
		for (int c = 0; c < ncols; ++c) {
			int atteso = c - r;
			int reale = mat[r*ncols + c];
			if (atteso != reale) {
				fprintf(stderr, "mismatch @ %d %d: %d != %d\n",
					r, c, reale, atteso);
				exit(2);
			}
		}
	}
}

void print_matrix (cl_int* m,int ncols,int nrows) {
	/*
	for (int i=0;i<ncols;i++) {
		printf ("\n");
		for (int j=0;j<nrows;j++) {
			printf ("%d ",m[i*nrows+j]);
		}
	}*/
	int c=0;

	for (int i=0;i<ncols*nrows;i++) {
		if (c==ncols) {
			c=0;
			printf ("\n");
		}
		printf ("%d ",m[i]);
		c++;
	}
	printf ("\n");
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		error("sintassi: transpose nrows ncols");

	const int nrows = atoi(argv[1]);
	const int ncols = atoi(argv[2]);
	const int numels = nrows*ncols;
	const size_t memsize = numels*sizeof(int);

	if (nrows <= 0 || ncols <= 0)
		error("nrows, ncols devono essere positivi");

	cl_platform_id p = select_platform();
	cl_device_id d = select_device(p);
	cl_context ctx = create_context(p, d);
	cl_command_queue que = create_queue(ctx, d);
	cl_program prog = create_program("transpose.ocl", ctx, d);

	cl_int err;

	cl_kernel matinit_k = clCreateKernel(prog, "matinit", &err);
	ocl_check(err, "create kernel matinit");

	cl_kernel trans_k = clCreateKernel(prog, "transpose4x4", &err);
	ocl_check(err, "create kernel trans");

	/* Allocazione buffer */
	cl_mem d_mat = clCreateBuffer(ctx,
		CL_MEM_READ_WRITE,
		memsize, NULL, &err);
	ocl_check(err, "create buffer mat");

	cl_mem d_trans = clCreateBuffer(ctx,
		CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY
		| CL_MEM_ALLOC_HOST_PTR,
		memsize, NULL, &err);
	ocl_check(err, "create buffer trans");

	cl_event evt_init = matinit(que, matinit_k,
		d_mat, nrows, ncols, 0, NULL);
	clFinish(que);
	printf("Init: %gms\t%g GB/s\n",
		runtime_ms(evt_init),
		(1.0*memsize)/runtime_ns(evt_init)
		);

	cl_int* mat_init = clEnqueueMapBuffer(que, d_mat,
		CL_TRUE, CL_MAP_READ,
		0, memsize,
		0, NULL, NULL, &err);
	ocl_check(err, "map buffer vsum");
	clFinish(que);

	//print_matrix(mat_init,ncols,nrows);

	err = clEnqueueUnmapMemObject(que, d_mat, mat_init,
		0, NULL, NULL);
	ocl_check(err, "unmap buffer vsum");
	clFinish(que);

	cl_event evt_trans = transpose(que, trans_k,
		d_mat, d_trans, nrows, ncols, 1, &evt_init);

	err = clFinish(que);
	ocl_check(err, "clFinish");
	printf("transpose: %gms\t%g GB/s\n",
		runtime_ms(evt_trans),
		(2.0*memsize)/runtime_ns(evt_trans)
		);

		cl_event evt_map, evt_unmap;

		cl_int *h_trans = clEnqueueMapBuffer(que, d_trans,
			CL_TRUE, CL_MAP_READ,
			0, memsize,
			0, NULL, &evt_map, &err);
		ocl_check(err, "map buffer vsum");
		clFinish(que);

		//print_matrix(h_trans,nrows,ncols);
		//verify(h_trans, ncols, nrows);

		err = clEnqueueUnmapMemObject(que, d_trans, h_trans,
			0, NULL, &evt_unmap);
		ocl_check(err, "unmap buffer vsum");
		clFinish(que);


	clReleaseMemObject(d_mat);
	clReleaseMemObject(d_trans);

	clReleaseKernel(matinit_k);
	clReleaseKernel(trans_k);
	clReleaseProgram(prog);
	clReleaseCommandQueue(que);
	clReleaseContext(ctx);
	return 0;
}
