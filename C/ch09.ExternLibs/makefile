#
#  Makefile for Chapter 5 of "Programming your GPU with OpenMP"
#
#  USAGE:
#     make          ... to build the program
#     make test     ... to run the default test case
#
#  LICENSE:  See ../../License
#
include ../make.def

# These examples expect the NVHPC implementation for compatibility with CUDA
ifneq ($(CC), nvc)
	$(error Expected the NVHPC compiler. Please choose the appropriate ../make.def file.)
endif
CUDA_LIB = $(shell dirname `which nvcc`)/../../cuda/lib64
CUBLAS_LIB = $(shell dirname `which nvcc`)/../../math_libs/lib64/

EXES=  CUDAKernel$(EXE) PrintfTargetAddresses$(EXE) InteropData$(EXE) AssociatePtr$(EXE) InteropCUDA$(EXE) InteropAsync$(EXE)

all: $(EXES)

CUDAKernel$(EXE): Fig9.1_CUDAKernel_full.cu
	nvcc -O3 -o CUDAKernel$(EXE) Fig9.1_CUDAKernel_full.cu

PrintfTargetAddresses$(EXE): Fig9.2_PrintfTargetAddresses_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o PrintfTargetAddresses$(EXE) Fig9.2_PrintfTargetAddresses_full.$(OBJ) $(LIBS)

InteropData$(EXE): Fig9.5_InteropData_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o InteropData$(EXE) Fig9.5_InteropData_full.$(OBJ) $(LIBS) -lcudart -lcublas -L$(CUDA_LIB) -L$(CUBLAS_LIB)

AssociatePtr$(EXE): Fig9.6_AssociatePtr_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o AssociatePtr$(EXE) Fig9.6_AssociatePtr_full.$(OBJ) -lcudart -L$(CUDA_LIB)

InteropCUDA$(EXE): Fig9.7_InteropCUDA_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o InteropCUDA$(EXE) Fig9.7_InteropCUDA_full.$(OBJ) $(LIBS) -lcudart -lcublas -L$(CUDA_LIB) -L$(CUBLAS_LIB)

InteropAsync$(EXE): Fig9.15_InteropAsync_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o InteropAsync$(EXE) Fig9.15_InteropAsync_full.$(OBJ) $(LIBS) -lcudart -lcublas -L$(CUDA_LIB) -L$(CUBLAS_LIB)

InteropDispatch$(EXE): nvidia.$(OBJ) Fig9.21_InteropDispatch_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o InteropDispatch$(EXE) Fig9.21_InteropDispatch_full.$(OBJ) nvidia.$(OBJ) $(LIBS) -lcudart -lcublas -L$(CUDA_LIB) -L$(CUBLAS_LIB)

test: $(EXES)
	$(PRE)PrintfTargetAddressess$(EXE)

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CPP) $(CFLAGS) -c $<
