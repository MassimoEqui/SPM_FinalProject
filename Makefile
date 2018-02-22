CC =g++
CFLAGS = -I.

.PHONY: all clean

main.out: main.o Node.o Const.o Var.o
	$(CC) $(CFLAGS) -o main.out main.o Node.o Const.o Var.o
	
main.o: ./src/main/main.cpp
	$(CC) $(CFLAGS) -c ./src/main/main.cpp 

Node.o: ./include/grammar/Node.h ./src/grammar/Node.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Node.cpp

Const.o: ./include/grammar/Const.h ./src/grammar/Const.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Const.cpp

Var.o: ./include/grammar/Var.h ./src/grammar/Var.cpp
	$(CC) $(CFLAGS) -c ./src/grammar/Var.cpp

clean:
	@for s in *.o ; do if [ -e $$s ] ; then rm $$s ; fi done
	@for s in *.out ; do if [ -e $$s ] ; then rm $$s ; fi done
	@echo "cleanup done"
