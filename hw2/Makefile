# ***
# *** DO NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = main.c count_frequency.c  
OBJS = $(SRCS:%.c=%.o)

pa2: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa2 

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: hw15  
	$(VAL) ./hw13 inputs/test6
#testing only input3 and output3

testall: test1 test2 test3 test4 test5 test6  

test1: pa2 		
	./pa2 original/gophers gophers.count 
	diff gophers.count count/gophers.count 

test2: pa2   
	./pa2 original/binary1 binary1.count
	diff binary1.count count/binary1.count 

test3: pa2 
	./pa2 original/empty empty.count
	diff empty.count count/empty.count 

test4: pa2 
	./pa2 original/lorum lorum.count
	diff lorum.count count/lorum.count 

test5: pa2 
	./pa2 original/stone stone.count
	diff stone.count count/stone.count 

test6: pa2 
	./pa2 original/woods woods.count
	diff woods.count count/woods.count 


clean: # remove all machine generated files
	rm -f pa2 *.o *.count output?
