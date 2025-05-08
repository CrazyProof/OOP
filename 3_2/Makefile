CXX = g++
CXXFLAGS = -std=c++11 -Wall
OBJ = main.o weapon.o dragon.o ninja.o fire_ninja.o ice_ninja.o
TARGET = main

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp ninja.h fire_ninja.h ice_ninja.h
	$(CXX) $(CXXFLAGS) -c main.cpp

weapon.o: weapon.cpp weapon.h
	$(CXX) $(CXXFLAGS) -c weapon.cpp

dragon.o: dragon.cpp dragon.h
	$(CXX) $(CXXFLAGS) -c dragon.cpp

ninja.o: ninja.cpp ninja.h
	$(CXX) $(CXXFLAGS) -c ninja.cpp

fire_ninja.o: fire_ninja.cpp fire_ninja.h
	$(CXX) $(CXXFLAGS) -c fire_ninja.cpp

ice_ninja.o: ice_ninja.cpp ice_ninja.h
	$(CXX) $(CXXFLAGS) -c ice_ninja.cpp

clean:
	rm -f $(OBJ) $(TARGET)
