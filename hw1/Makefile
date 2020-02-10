# ***
# *** DO NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS = -DTEST_CALCULATE -DTEST_READLIST -DTEST_DELETELIST -DTEST_ADDNODE -DTEST_DELETENODE 

SRCS = pa1.c shell_list.c shell_array.c 
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa1

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: hw13  
	$(VAL) ./hw13 inputs/test6
#testing only input3 and output3

testall: test1 test2 test3 test4 test5 test6  

test1: pa1 
	./pa1 examples/15.b 15_sorted.b  

test2: pa1 
	./pa1 examples/1K.b 1K_sorted.b
	diff 1K_sorted.b examples/1Ksl.b

test3: pa1  
	./pa1 examples/10K.b 10K_sorted.b 

test4: pa1 		
	./pa1 examples/100K.b 100K_sorted.b 

test5: pa1 
	./pa1 examples/1M.b 1M_sorted.b

test6: hw13 
	./hw13 inputs/test6 > output6 
	diff output6 expected/expected6 


clean: # remove all machine generated files
	rm -f pa1 *.o ?_sorted.b
