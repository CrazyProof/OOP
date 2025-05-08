CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = main
OBJS = main.o ChatUser.o ChatSession.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp ChatUser.h ChatSession.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ChatUser.o: ChatUser.cpp ChatUser.h
	$(CXX) $(CXXFLAGS) -c ChatUser.cpp

ChatSession.o: ChatSession.cpp ChatSession.h
	$(CXX) $(CXXFLAGS) -c ChatSession.cpp

clean:
	rm -f $(TARGET) $(OBJS)
