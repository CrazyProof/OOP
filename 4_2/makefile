all: main

main: main.o Alice.o Bob.o Part.o Robot.o
	g++ main.o Alice.o Bob.o Part.o Robot.o -o main

main.o: main.cpp Alice.h Bob.h Part.h Robot.h
	g++	-c main.cpp -o main.o

Alice.o: Alice.h Alice.cpp Robot.h
	g++ -c Alice.cpp -o Alice.o

Bob.o: Bob.h Bob.cpp Robot.h
	g++ -c Bob.cpp -o Bob.o

Part.o: Part.h Part.cpp
	g++ -c Part.cpp -o Part.o

Robot.o: Robot.h Robot.cpp
	g++ -c Robot.cpp -o Robot.o

.phony:clean
clean:
	del -f *.o *.exe
