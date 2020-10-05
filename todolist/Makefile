all: todolist

todolist: todolist-test.cpp todolist.o
	g++ -g -Wall -std=c++11 todolist-test.cpp todolist.o -o todolist-test

todolist.o: todolist.cpp todolist.h
	g++ -g -Wall -c todolist.cpp -o todolist.o


clean: 
	rm -f *.o todolist