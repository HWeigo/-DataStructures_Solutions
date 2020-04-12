WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = pa5.c sorting.c 
OBJS = $(SRCS:%.c=%.o)

pa5: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa5

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa4
	$(VAL) ./pa4 examples/3.po 8.pr 8.dim 8.pck 

testmemoryAVL: pa4
	$(VAL) ./pa4 examples/ops3.b tree3.b

testall: test1a test2a test1l test2l 
testallAVL: testAVL0 testAVL1 testAVL2 testAVL3

testB2T: pa4
	./pa4 examples/ops2.b ops2.txt
	./pa4 examples/tree2.b tree2.txt 

testT2B: pa4
	./pa4 examples/ops2.txt ops2.b
	./pa4 examples/tree2.txt tree2.b 

testq0: pa5  
	./pa5 -q examples/15.b outputs/15.b
	diff outputs/15.b examples/15_sa.b

testq1: pa5 
	./pa5 -q examples/1K.b outputs/1K.b
	diff outputs/1K.b examples/1K_sa.b

testq2: pa5 
	./pa5 -q examples/10K.b outputs/10K.b
	diff outputs/10K.b examples/10K_sa.b

testq3: pa5 
	./pa5 -q examples/100K.b outputs/100K.b
	diff outputs/100K.b examples/100K_sa.b

testq4: pa5 
	./pa5 -q examples/1M.b outputs/1M.b
	diff outputs/1M.b examples/1M_sa.b

testEvaluate2: pa4 
	./pa4 -e examples/invalidtree1.b 

testEvaluate3: pa4 
	./pa4 -e examples/invalidtree2.b 

testAVL0: pa4  
	./pa4 -b examples/ops0.b tree0.b
	diff tree0.b examples/tree0.b 

testAVL1: pa4  
	./pa4 -b examples/ops1.b tree1.b
	diff tree1.b examples/tree1.b 

testAVL2: pa4  
	./pa4 -b examples/ops2.b tree2.b
	diff tree2.b examples/tree2.b 

testAVL3: pa4  
	./pa4 -b examples/ops3.b tree3.b
	diff tree3.b examples/tree3.b 

clean: # remove all machine generated files
	rm -f pa4 *.o *.b *.txt memcheck.txt
