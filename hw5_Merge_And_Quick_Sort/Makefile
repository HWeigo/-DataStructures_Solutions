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

testmemory: pa5 
	$(VAL) ./pa5 -m examples/10K.b outputs/10K.b

testall: testallMergeSort testallQuickSort 
testallQuickSort: testq0 testq1 testq2 testq3 testq4 
testallMergeSort: testm0 testm1 testm2 testm3 testm4 


testB2T: pa4
	./pa4 examples/ops2.b ops2.txt
	./pa4 examples/tree2.b tree2.txt 

testT2B: pa4
	./pa4 examples/ops2.txt ops2.b
	./pa4 examples/tree2.txt tree2.b 

testq0: pa5  
	./pa5 -q examples/15.b outputs/15_q.b
	diff outputs/15_q.b examples/15_sa.b

testq1: pa5 
	./pa5 -q examples/1K.b outputs/1K_q.b
	diff outputs/1K_q.b examples/1K_sa.b

testq2: pa5 
	./pa5 -q examples/10K.b outputs/10K_q.b
	diff outputs/10K_q.b examples/10K_sa.b

testq3: pa5 
	./pa5 -q examples/100K.b outputs/100K_q.b
	diff outputs/100K_q.b examples/100K_sa.b

testq4: pa5 
	./pa5 -q examples/1M.b outputs/1M_q.b
	diff outputs/1M_q.b examples/1M_sa.b

testm0: pa5  
	./pa5 -m examples/15.b outputs/15_m.b
	diff outputs/15_m.b examples/15_sa.b

testm1: pa5 
	./pa5 -m examples/1K.b outputs/1K_m.b
	diff outputs/1K_m.b examples/1K_sa.b

testm2: pa5 
	./pa5 -m examples/10K.b outputs/10K_m.b
	diff outputs/10K_m.b examples/10K_sa.b

testm3: pa5 
	./pa5 -m examples/100K.b outputs/100K_m.b
	diff outputs/100K_m.b examples/100K_sa.b

testm4: pa5 
	./pa5 -m examples/1M.b outputs/1M_m.b
	diff outputs/1M_m.b examples/1M_sa.b

clean: # remove all machine generated files
	rm -f pa5 *.o outputs/*.b memcheck.txt
