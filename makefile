CXX=g++
CXXFLAGS=-std=c++11 -Wall
LDFLAGS=
SOURCES=thomfetch.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=thomfetch

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
