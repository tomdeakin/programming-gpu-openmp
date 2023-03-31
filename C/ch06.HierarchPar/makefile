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

EXES=  vaddDistribute$(EXE) vaddDistributeParallelFor$(EXE)

all: $(EXES)

vaddDistribute$(EXE): Fig6.6_VaddDistribute_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o vaddDistribute$(EXE) Fig6.6_VaddDistribute_full.$(OBJ) $(LIBS)

vaddDistributeParallelFor$(EXE): Fig6.7_VaddDistributeParallelFor_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o vaddDistributeParallelFor$(EXE) Fig6.7_VaddDistributeParallelFor_full.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)vaddDistribute$(EXE) 
	$(PRE)vaddDistributeParallelFor$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
