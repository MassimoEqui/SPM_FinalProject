CC =g++
CFLAGS = -I. -std=c++11 -g

.PHONY: allTests clean
	
main.out: main.o Node.o Const.o Var.o Leaf.o Tree.o
	$(CC) $(CFLAGS) -o main.out main.o Node.o Const.o Var.o Leaf.o Tree.o

main.o: ./src/main/main.cpp
	$(CC) $(CFLAGS) -c ./src/main/main.cpp

Node.o: ./include/grammar/Node.h ./src/grammar/Node.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Node.cpp

Const.o: ./include/grammar/Const.h ./src/grammar/Const.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Const.cpp

Var.o: ./include/grammar/Var.h ./src/grammar/Var.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Var.cpp

Leaf.o: ./include/grammar/Leaf.h ./src/grammar/Leaf.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Leaf.cpp

Tree.o: ./include/genetics/Tree.h ./src/genetics/Tree.cpp
	$(CC) $(CFLAGS) -c ./src/genetics/Tree.cpp

clean:
	@for s in *.o ; do if [ -e $$s ] ; then rm $$s ; fi done
	@for s in *.out ; do if [ -e $$s ] ; then rm $$s ; fi done
	@echo "cleanup done"

allTests:
	$(CC) $(CFLAGS) -c ./src/test/test_*.cpp
	@for s in test_*.o ; do \
	$(CC) $(CFLAGS) -o $${s%.o}.out $$s Node.o Const.o Var.o Leaf.o Tree.o ; \
	echo $${s%.o}.out compiled ; \
	done
