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

EXES=  GetNumDevices$(EXE) VecaddMultiGPU$(EXE) VecaddMultiGPUNowait$(EXE) DotProdMultiGPU$(EXE) DotprodMultiGPUTaskgroup$(EXE)

all: $(EXES)

GetNumDevices$(EXE): Fig8.2_GetNumDevices.$(OBJ)
	$(CLINKER) $(CFLAGS) -o GetNumDevices$(EXE) Fig8.2_GetNumDevices.$(OBJ) $(LIBS)

VecaddMultiGPU$(EXE): Fig8.4_VecaddMultiGPU_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o VecaddMultiGPU$(EXE) Fig8.4_VecaddMultiGPU_full.$(OBJ) $(LIBS)

VecaddMultiGPUNowait$(EXE): Fig8.7_VecaddMultiGPUNowait_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o VecaddMultiGPUNowait$(EXE) Fig8.7_VecaddMultiGPUNowait_full.$(OBJ) $(LIBS)

DotProdMultiGPU$(EXE): Fig8.12_DotProdMultiGPU_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o DotProdMultiGPU$(EXE) Fig8.12_DotProdMultiGPU_full.$(OBJ) $(LIBS)

DotprodMultiGPUTaskgroup$(EXE): Fig8.13_DotprodMultiGPUTaskgroup_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o DotprodMultiGPUTaskgroup$(EXE) Fig8.13_DotprodMultiGPUTaskgroup_full.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)GetNumDevices$(EXE)
	$(PRE)VecaddMultiGPU$(EXE)
	$(PRE)VecaddMultiGPUNowait$(EXE)
	$(PRE)DotProdMultiGPU$(EXE)

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
