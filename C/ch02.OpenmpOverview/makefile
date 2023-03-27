#
#  Makefile for Chapter 2 of "Programming your GPU with OpenMP"
#
#  USAGE:
#     make          ... to build the programs
#     make test     ... to run the default test cases
#
#  LICENSE:  See ../../License
#
include ../make.def

EXES=  hello$(EXE) pi_seq$(EXE) pi_spmd$(EXE) pi_loop$(EXE)

all: $(EXES)

hello $(EXE): Fig2.3_hello.$(OBJ)  
	$(CLINKER) $(CFLAGS) -o hello $(EXE) Fig2.3_hello.$(OBJ)   $(LIBS)
	
pi_seq $(EXE): Fig2.5_pi_seq.$(OBJ)  
	$(CLINKER) $(CFLAGS) -o pi_seq$(EXE) Fig2.5_pi_seq.$(OBJ)   $(LIBS)

pi_spmd $(EXE): Fig2.6_pi_spmd.$(OBJ)  
	$(CLINKER) $(CFLAGS) -o pi_spmd$(EXE) Fig2.6_pi_spmd.$(OBJ)   $(LIBS)

pi_loop $(EXE): Fig2.7_pi_loop.$(OBJ)  
	$(CLINKER) $(CFLAGS) -o pi_loop$(EXE) Fig2.7_pi_loop.$(OBJ)   $(LIBS)

test: $(EXES)
	$(PRE)hello$(EXE) 
	$(PRE)pi_seq$(EXE) 
	$(PRE)pi_spmd$(EXE) 
	$(PRE)pi_loop$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
