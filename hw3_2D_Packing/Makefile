# ***
# *** DO NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = pa3.c tree_construct.c
OBJS = $(SRCS:%.c=%.o)

pa3: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa3 

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa3  
	$(VAL) ./pa3 examples/3.po
#testing only input3 and output3

testall: test1a test2a test1l test2l 

test1a: pa1 
	./pa1 -a examples/15.b 15_sa.b  
	diff 15_sa.b examples/15sa.b  

test2a: pa1 
	./pa1 -a examples/1K.b 1K_sa.b
	diff  1K_sa.b examples/1Ksa.b

test3a: pa1  
	./pa1 -a examples/10K.b 10K_sa.b 

test4a: pa1 		
	./pa1 -a examples/100K.b 100K_sa.b 

test5a: pa1 
	./pa1 -a examples/1M.b 1M_sa.b

test1l: pa1 
	./pa1 -l examples/15.b 15_sl.b  
	diff 15_sl.b examples/15sl.b   

test2l: pa1 
	./pa1 -l examples/1K.b 1K_sl.b
	diff  1K_sl.b examples/1Ksl.b 

test3l: pa1  
	./pa1 -l examples/10K.b 10K_sl.b 

test4l: pa1 		
	./pa1 -l examples/100K.b 100K_sl.b 

test5l: pa1 
	./pa1 -l examples/1M.b 1M_sl.b

clean: # remove all machine generated files
	rm -f pa3 *.o *.b memcheck.txt
