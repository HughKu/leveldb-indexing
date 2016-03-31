all:	main.o
	g++ main.o -o main -lleveldb -lboost_system

main.o:	main.cpp
	g++ -c main.cpp

clean:
	rm -rf main.o
