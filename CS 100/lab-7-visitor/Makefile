CC = g++
CC_FLAGS = -Wall -Werror -ansi -pedantic -std=c++11 -O3

EXECUTABLE = visitor

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
