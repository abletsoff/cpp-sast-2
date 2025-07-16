CXX = g++
CXXFLAGS = -std=c++11 -Wall
LWS_CFLAGS = $(shell pkg-config --cflags libwebsockets)
LWS_LIBS = $(shell pkg-config --libs libwebsockets)
SOURCES = main.cpp handlers.cpp utils.cpp
HEADERS = handlers.h utils.h
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = vuln_ws_server

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LWS_LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(LWS_CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)
