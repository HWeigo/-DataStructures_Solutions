# ***
# *** DO NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla #-Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS =  

SRCS = main.c count_frequency.c tree_construct.c encode.c compress.c
OBJS = $(SRCS:%.c=%.o)

pa2: $(OBJS)
	$(GCC) $(TESTFALGS) $(OBJS) -o pa2 

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

testmemory: pa2  
	$(VAL) ./pa2 original/gophers memtest.count
#testing only input3 and output3

testall: test1 test2 test3 test4 test5 test6  

test1: pa2 		
	./pa2 original/gophers gophers.count gophers.tree gophers.code gophers.hbt 
	diff gophers.count count/gophers.count
	diff gophers.tree tree/gophers.tree 
	diff gophers.code code/gophers.code 

test2: pa2   
	./pa2 original/binary1 binary1.count binary1.tree binary1.code binary1.hbt 
	diff binary1.count count/binary1.count 
	diff binary1.tree tree/binary1.tree 
	diff binary1.code code/binary1.code 

test3: pa2 
	./pa2 original/empty empty.count empty.code 
	diff empty.count count/empty.count 
	diff empty.tree tree/empty.tree 
	diff empty.code code/empty.code 

test4: pa2 
	./pa2 original/lorum lorum.count lorum.tree lorum.code lorum.hbt 
	diff lorum.count count/lorum.count  
	diff lorum.tree tree/lorum.tree 
	diff lorum.code code/lorum.code 

test5: pa2 
	./pa2 original/stone stone.count stone.code 
	diff stone.count count/stone.count  
	diff stone.code code/stone.code 

test6: pa2 
	./pa2 original/woods woods.count woods.code 
	diff woods.count count/woods.count
	diff woods.code code/woods.code 

clean: # remove all machine generated files
	rm -f pa2 *.o *.count *.code *.hbt memcheck.txt output?
