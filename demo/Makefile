CC=clang++
CFLAGS  = -g -Wall -Weffc++ -std=c++11
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
