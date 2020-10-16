output: main.o Labirinto.o Node.o
	g++ main.o Labirinto.o Node.o -o output

main.o: main.cpp
	g++ -c main.cpp

Node.o: Node.h
	g++ -c Node.cpp

Labirinto.o: Labirinto.h
	g++ -c Labirinto.cpp