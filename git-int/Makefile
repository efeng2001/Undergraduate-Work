all: GitInt

GitInt: gitint-shell.cpp gitint.o
	g++ -g -Wall -std=c++11 gitint-shell.cpp gitint.o -o test

gitint.o: gitint.cpp gitint.h
	g++ -g -Wall -c gitint.cpp -o gitint.o

clean: rm -f *.o test