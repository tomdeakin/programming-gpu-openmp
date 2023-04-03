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

EXES=  DeclareTargetVariable$(EXE) VaddSpan$(EXE) Mapper$(EXE) VaddUSM$(EXE) VaddMapAlloc$(EXE) AlwaysMap$(EXE)

all: $(EXES)

DeclareTargetVariable$(EXE): Fig7.11_DeclareTargetVariable.$(OBJ)
	$(CLINKER) $(CFLAGS) -o DeclareTargetVariable$(EXE) Fig7.11_DeclareTargetVariable.$(OBJ) $(LIBS)

VaddSpan$(EXE): Fig7.14_VaddSpan_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o VaddSpan$(EXE) Fig7.14_VaddSpan_full.$(OBJ) $(LIBS)

Mapper$(EXE): Fig7.15_Mapper_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o Mapper$(EXE) Fig7.15_Mapper_full.$(OBJ) $(LIBS)

VaddUSM$(EXE): Fig7.24_VaddUSM_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o VaddUSM$(EXE) Fig7.24_VaddUSM_full.$(OBJ) $(LIBS)

VaddMapAlloc$(EXE): Fig7.3_VaddMapAlloc_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o VaddMapAlloc$(EXE) Fig7.3_VaddMapAlloc_full.$(OBJ) $(LIBS)

AlwaysMap$(EXE): Fig7.4_AlwaysMap_full.$(OBJ)
	$(CLINKER) $(CFLAGS) -o AlwaysMap$(EXE) Fig7.4_AlwaysMap_full.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)DeclareTargetVariable$(EXE)
	$(PRE)VaddSpan$(EXE)
	$(PRE)Mapper$(EXE)
	$(PRE)VaddUSM$(EXE)
	$(PRE)VaddMapAlloc$(EXE)
	$(PRE)AlwaysMap$(EXE)

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
