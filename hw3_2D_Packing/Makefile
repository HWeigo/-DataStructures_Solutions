# ***
# *** DO NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = pa3.c tree_construct.c packing_operation.c
OBJS = $(SRCS:%.c=%.o)

pa3: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa3 

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa3  
	$(VAL) ./pa3 examples/3.po 8.pr 8.dim 8.pck 
#testing only input3 and output3

testall: test1a test2a test1l test2l 

test1: pa3 
	./pa3 examples/3.po 3.pr 3.dim 3.pck 
	diff 3.pr examples/3.pr 
	diff 3.dim examples/3.dim 
	diff 3.pck examples/3.pck 

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
	rm -f pa3 *.o *.pr *.pck *.dim memcheck.txt
