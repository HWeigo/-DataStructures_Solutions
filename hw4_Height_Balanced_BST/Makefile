# ***
# *** DO NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = main.c file_converter.c evaluation.c tree.c avl_constructor.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa4

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa4
	$(VAL) ./pa4 examples/3.po 8.pr 8.dim 8.pck 
#testing only input3 and output3

testall: test1a test2a test1l test2l 

testB2T: pa4
	./pa4 examples/ops2.b ops2.txt
	./pa4 examples/tree2.b tree2.txt 

testT2B: pa4
	./pa4 examples/ops2.txt ops2.b
	./pa4 examples/tree2.txt tree2.b 

testEvaluate: pa4 
	./pa4 examples/tree2.b

test2: pa3 
	./pa3 examples/8.po 8.pr 8.dim 8.pck 
	diff 8.pr examples/8.pr 
	diff 8.dim examples/8.dim 
	diff 8.pck examples/8.pck

test3: pa3
	./pa3 examples/500.po 500.pr 500.dim 500.pck 

test4: pa3 		
	./pa3 examples/100.po 100.pr 100.dim 100.pck 

test5: pa3 
	./pa3 examples/1K.po 1K.pr 1K.dim 1K.pck 

clean: # remove all machine generated files
	rm -f pa4 *.o *.b *.txt memcheck.txt
