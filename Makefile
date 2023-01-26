all: PQdemo

PQdemo: PQdemo.o  
	g++ -Wall -o PQdemo PQdemo.o

PQdemo.o: PQdemo.cpp PQ.h AvlTree.h
	g++ -Wall -o PQdemo.o -c PQdemo.cpp

clean:
	rm -f PQdemo *.o
