CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = main
OBJS = main.o Student.o ClassSystem.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Student.h ClassSystem.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Student.o: Student.cpp Student.h
	$(CXX) $(CXXFLAGS) -c Student.cpp

ClassSystem.o: ClassSystem.cpp ClassSystem.h Student.h
	$(CXX) $(CXXFLAGS) -c ClassSystem.cpp

clean:
	rm -f $(TARGET) $(OBJS)
