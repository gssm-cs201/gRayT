#clang++ example.cpp -L ../lib/ -lgssmraytracer -I ../include/ -std=c++11
CC=clang++
CFLAGS  = -Wall -Weffc++ -std=c++11
SOURCES = $(wildcard *.cpp)
LDFLAGS = -L ../lib/ -lgssmraytracer -lglut -lGL -lGLU -lm
INCLUDES = -I ../include/
EXECUTABLE = example

all: $(EXECUTABLE)

.PHONY : $(EXECUTABLE)
$(EXECUTABLE):
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LDFLAGS) -o $@

.PHONY : clean
clean:
	rm -fr $(EXECUTABLE)
