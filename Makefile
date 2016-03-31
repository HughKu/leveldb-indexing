all:	main.o
	g++ main.o -o main -lleveldb

main.o:	main.cpp
	g++ -c main.cpp

clean:
	rm -rf main.o
