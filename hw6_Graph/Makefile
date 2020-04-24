WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = main.c file_converter.c graph.c 
OBJS = $(SRCS:%.c=%.o)

pa6: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa6

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa6
	$(VAL) ./pa6 -s examples/4_4.b  

testall: testallMergeSort testallQuickSort 
testallQuickSort: testq0 testq1 testq2 testq3 testq4 
testallMergeSort: testm0 testm1 testm2 testm3 testm4 


testB2T: pa6
	./pa6 -c examples/4_4.b 4_4_hw.t
	diff 4_4_hw.t examples/4_4.t 

testT2B: pa4
	./pa4 examples/ops2.txt ops2.b
	./pa4 examples/tree2.txt tree2.b 

tests44: pa6   
	./pa6 -s examples/4_4.b  

tests45: pa6
	./pa6 -s examples/4_5.b
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
	rm -f pa6 *.t 
