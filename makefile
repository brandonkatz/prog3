prog3: main.o sequencer.o 
	g++ main.o sequencer.o  -o prog3

main.o: main.cpp sequencer.h 
	g++ -g -c main.cpp

sequencer.o: sequencer.cpp sequencer.h
	g++ -g -c sequencer.cpp 

clean:
	rm prog3 main.o sequencer.o

all:
	make prog3 main.o sequencer.o 