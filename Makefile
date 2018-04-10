CC =g++
CFLAGS = -I. -I$(HOME)/fastflow -std=c++11 -DNO_DEFAULT_MAPPING -g -O3
OBJECTS = main.o Node.o Const.o Var.o Leaf.o Tree.o Forest.o

.PHONY: test clean
	
main.out: $(OBJECTS)
	$(CC) -O3 $(CFLAGS) $(OBJECTS) -o main.out

main.o: ./src/main/main.cpp ./src/main/evolution_cycle.hpp
	$(CC) $(CFLAGS) -c ./src/main/main.cpp

Node.o: ./include/grammar/Node.h ./include/grammar/INode.h ./src/grammar/Node.cpp 
	$(CC) $(CFLAGS) -c ./src/grammar/Node.cpp

Const.o: ./include/grammar/Const.h ./include/grammar/INode.h ./src/grammar/Const.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Const.cpp

Var.o: ./include/grammar/Var.h ./include/grammar/INode.h ./src/grammar/Var.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Var.cpp

Leaf.o: ./include/grammar/Leaf.h ./include/grammar/INode.h ./src/grammar/Leaf.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Leaf.cpp

Tree.o: ./include/genetics/Tree.h ./include/grammar/INode.h ./src/genetics/Tree.cpp
	$(CC) $(CFLAGS) -c ./src/genetics/Tree.cpp

Forest.o: ./include/genetics/Forest.h ./include/grammar/INode.h ./src/genetics/Forest.cpp
	$(CC) $(CFLAGS) -c ./src/genetics/Forest.cpp

clean:
	@for s in *.o ; do if [ -e $$s ] ; then rm $$s ; fi done
	@for s in *.out ; do if [ -e $$s ] ; then rm $$s ; fi done
	@echo "cleanup done"

test:
	$(CC) $(CFLAGS) -c ./src/test/test_*.cpp
	@for s in test_*.o ; do \
	$(CC) $(CFLAGS) -o $${s%.o}.out $$s Node.o Const.o Var.o Leaf.o Tree.o Forest.o ; \
	echo $${s%.o}.out compiled ; \
	done
