all: Search

Search: search-shell.cpp cmdhandler.o handler.o md_parser.o searcheng.o searchui.o txt_parser.o util.o webpage.o
	g++ -g -Wall -std=c++11 search-shell.cpp cmdhandler.o handler.o md_parser.o searcheng.o searchui.o txt_parser.o util.o webpage.o -o search-shell

cmdhandler.o: cmdhandler.cpp cmdhandler.h
	g++ -g -Wall -c cmdhandler.cpp -o cmdhandler.o

handler.o: handler.cpp handler.h
	g++ -g -Wall -c handler.cpp -o handler.o

md_parser.o: md_parser.cpp md_parser.h
	g++ -g -Wall -c md_parser.cpp -o md_parser.o

searcheng.o: searcheng.cpp searcheng.h
	g++ -g -Wall -c searcheng.cpp -o searcheng.o

searchui.o: searchui.cpp searchui.h
	g++ -g -Wall -c searchui.cpp -o searchui.o

txt_parser.o: txt_parser.cpp txt_parser.h
	g++ -g -Wall -c txt_parser.cpp -o txt_parser.o

util.o: util.cpp util.h
	g++ -g -Wall -c util.cpp -o util.o

webpage.o: webpage.cpp webpage.h
	g++ -g -Wall -c webpage.cpp -o webpage.o


clean: 
	rm -f *.o Search