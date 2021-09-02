#define CL_TARGET_OPENCL_VERSION 120
#include <stdio.h>
#include <stdlib.h>
#include "../lib/ocl_boiler.h"
#include "../VectorialRuntime.h"

int main (int argc, char** argv) {
   struct VectorialRuntime a;
   scanDevices(&a); 
   printf("");
}