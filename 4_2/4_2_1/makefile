all: main

main: main.o Alice.o Bob.o Part.o
	g++ main.o Alice.o Bob.o Part.o -o main

main.o:  main.cpp Alice.h Bob.h Part.h
	g++	-c main.cpp -o main.o

Alice.o: Alice.h Alice.cpp
	g++ -c Alice.cpp -o Alice.o

Bob.o: Bob.h Bob.cpp
	g++ -c Bob.cpp -o Bob.o

Part.o: Part.h Part.cpp
	g++ -c Part.cpp -o Part.o

.phony:clean
clean:
	del -f *.o *.exe
