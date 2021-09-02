CFLAGS=-g -Wall -std=c99 -O3 -march=native
LDLIBS=-lOpenCL -lm
#LDLIBS=-framework OpenCL # su macOS

TARGETS = vecsum vecsum_vec vecsum2
TARGETS+= vecsmooth vecsmooth_lmem
TARGETS+= vecsmooth_lmem_regs vecsmooth_lmem2
TARGETS+= vecsmooth_vec
TARGETS+= transpose transpose4 transpose4x4
TARGETS+= transpose_local transpose_lmod
TARGETS+= transpose_pitch
TARGETS+= transpose-img
TARGETS+= imgcpy
TARGETS+= riduzione-somma2
TARGETS+= riduzione-sommax
TARGETS+= riduzione-sommax-lmem

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
