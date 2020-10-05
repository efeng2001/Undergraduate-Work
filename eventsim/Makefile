all: eventsim

eventsim: eventsim.cpp derived_events.o input_reader.o streetgrid.o
	g++ -g -Wall -std=c++11 eventsim.cpp derived_events.o input_reader.o streetgrid.o -o eventsim

derived_events.o: derived_events.cpp derived_events.h event.h
	g++ -g -Wall -c derived_events.cpp -o derived_events.o

input_reader.o: input_reader.cpp input_reader.h
	g++ -g -Wall -c input_reader.cpp -o input_reader.o

streetgrid.o: streetgrid.cpp streetgrid.h 
	g++ -g -Wall -c streetgrid.cpp -o streetgrid.o