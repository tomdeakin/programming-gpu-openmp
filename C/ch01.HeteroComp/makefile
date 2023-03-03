#
#  Makefile for Chapter 1 of "Programming your GPU with OpenMP"
#
#  USAGE:
#     make          ... to build the program
#     make test     ... to run the default test case
#
#  LICENSE:  See ../../License
#
include ../make.def

EXES=  vadd$(EXE) vadd_unrolled$(EXE) vadd_SIMD$(EXE)


all: $(EXES)

vadd $(EXE): Fig1.3_vadd.$(OBJ)  
	$(CLINKER) $(CFLAGS) -o vadd $(EXE) Fig1.3_vadd.$(OBJ)   $(LIBS)
	
vadd_unrolled$(EXE): Fig1.4_vadd_unrolled.$(OBJ)  
	$(CLINKER) $(CFLAGS) -o vadd_unrolled$(EXE) Fig1.4_vadd_unrolled.$(OBJ)   $(LIBS)
	
vadd_SIMD$(EXE): Fig1.5_vadd_SIMD.$(OBJ)  
	$(CLINKER) $(CFLAGS) -o vadd_SIMD$(EXE) Fig1.5_vadd_SIMD.$(OBJ) -Wpsabi  $(LIBS)$(EXE): pi.$(OBJ)  

test: $(EXES)
	$(PRE)vadd$(EXE) 
	$(PRE)vadd_unrolled$(EXE) 
	$(PRE)vadd_SIMD$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
