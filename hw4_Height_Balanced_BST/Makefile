# ***
# *** DO NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = main.c file_converter.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa4

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa4
	$(VAL) ./pa4 examples/3.po 8.pr 8.dim 8.pck 
#testing only input3 and output3

testall: test1a test2a test1l test2l 

test1: pa4 
	./pa4 examples/ops0.txt ops0.b 

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
