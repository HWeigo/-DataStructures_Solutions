WARNING = -pedantic -Wvla -Wall -Wshadow -O3
GCC = gcc -std=c99 $(WARNING) 
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = main.c file_converter.c graph.c evaluation.c 
OBJS = $(SRCS:%.c=%.o)

pa6: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa6

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemorys: pa6
	$(VAL) ./pa6 -s examples/5_5.b outputs/5_5.t outputs/5_5.s 

testmemorye: pa6
	$(VAL) ./pa6 -e examples/10_10.b outputs/10_10.s 

testmemoryh: pa6
	$(VAL) ./pa6 -e ta se

testall: testallMergeSort testallQuickSort 
testalls: tests44 tests45 tests55 tests1010 
testalle: teste44 teste4400 teste4410 teste4411 

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

teste4400: pa6
	./pa6 -e examples/4_4.b examples/4_4_00.s

teste4410: pa6
	./pa6 -e examples/4_4.b examples/4_4_10.s

teste4411: pa6
	./pa6 -e examples/4_4.b examples/4_4_11.s
clean: # remove all machine generated files
	rm -f pa6 *.o *.t memcheck.txt outputs/*.t outputs/*.s 
