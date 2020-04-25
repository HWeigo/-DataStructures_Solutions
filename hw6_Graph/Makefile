WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = main.c file_converter.c graph.c evaluation.c 
OBJS = $(SRCS:%.c=%.o)

pa6: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa6

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa6
	$(VAL) ./pa6 -s examples/5_5.b outputs/5_5.t outputs/5_5.s 

testall: testallMergeSort testallQuickSort 
testalls: tests44 tests45 tests55 tests1010 
testallMergeSort: testm0 testm1 testm2 testm3 testm4 


testB2T: pa6
	./pa6 -c examples/4_4.b 4_4_hw.t
	diff 4_4_hw.t examples/4_4.t 

testT2B: pa4
	./pa4 examples/ops2.txt ops2.b
	./pa4 examples/tree2.txt tree2.b 

tests44: pa6   
	./pa6 -s examples/4_4.b outputs/4_4.t outputs/4_4.s 
	diff outputs/4_4.t examples/4_4.t
	diff outputs/4_4.s examples/4_4.s 

tests45: pa6
	./pa6 -s examples/4_5.b outputs/4_5.t outputs/4_5.s 
	diff outputs/4_5.t examples/4_5.t
	diff outputs/4_5.s examples/4_5.s

tests55: pa6
	./pa6 -s examples/5_5.b outputs/5_5.t outputs/5_5.s 
	diff outputs/5_5.t examples/5_5.t
	diff outputs/5_5.s examples/5_5.s 

tests1010: pa6
	./pa6 -s examples/10_10.b outputs/10_10.t outputs/10_10.s
	diff outputs/10_10.t examples/10_10.t
	diff outputs/10_10.s examples/10_10.s 

teste44: pa6
	./pa6 -e examples/4_4.b examples/4_4.s

clean: # remove all machine generated files
	rm -f pa6 *.o *.t memcheck.txt outputs/*.t outputs/*.s 
