#clang++ example.cpp -L ../lib/ -lgssmraytracer -I ../include/ -std=c++11
CC=clang++
CFLAGS  = -Wall -std=c++11
SOURCES = example.cpp
LDFLAGS = -L ../lib/ -lgssmraytracer
INCLUDES = -I ../include/
EXECUTABLE = example

all: $(EXECUTABLE)

.PHONY : $(EXECUTABLE)
$(EXECUTABLE):
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LDFLAGS) -o $@ 

.PHONY : clean
clean:
	rm -fr $(EXECUTABLE)
