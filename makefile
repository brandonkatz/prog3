prog3: main.o
	g++ main.o -o prog3

main.o: main.cpp  
	g++ -g -c main.cpp

clean:
	rm prog3 main.o 

all:
	make prog3 main.o 