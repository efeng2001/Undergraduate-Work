all: llrec

llrec: llrec-test.cpp llrec.o
	g++ -g -Wall -std=c++11 llrec-test.cpp llrec.o -o llrec-test

llrec.o: llrec.cpp llrec.h
	g++ -g -Wall -c llrec.cpp -o llrec.o


clean: 
	rm -f *.o llrec