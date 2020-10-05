all: traversal

traversal: expr-tester.cpp expr-reader.o expr-ops.o
	g++ -g -Wall -std=c++11 expr-tester.cpp expr-reader.o expr-ops.o -o expr-tester

expr-reader.o: expr-reader.cpp expr-reader.h
	g++ -g -Wall -c expr-reader.cpp -o expr-reader.o

expr-ops.o: expr-ops.cpp expr-ops.h
	g++ -g -Wall -c expr-ops.cpp -o expr-ops.o

clean: 
	rm -f *.o llrec