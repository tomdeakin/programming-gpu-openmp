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

EXES=  jacobi$(EXE) jacobi2$(EXE) stencil$(EXE)


all: $(EXES)

jacobi$(EXE): Fig5.1_JacobiSolver_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o jacobi$(EXE) Fig5.1_JacobiSolver_full.$(OBJ) $(LIBS)

jacobi2$(EXE): Fig5.2_JacobiSolver2_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o jacobi2$(EXE) Fig5.2_JacobiSolver2_full.$(OBJ) $(LIBS)

stencil$(EXE): Fig5.3_stencil_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o stencil$(EXE) Fig5.3_stencil_full.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)jacobi$(EXE) 
	$(PRE)jacobi2$(EXE) 
	$(PRE)stencil$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
