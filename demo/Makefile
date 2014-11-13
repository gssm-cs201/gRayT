CC=g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11
SOURCES = $(wildcard *.cpp)
LDFLAGS = -L ../lib/ -lgssmraytracer -lglut -lGL -lGLU -lm -L /usr/local/lib -Wl,-Bstatic -lImath -lIex -Wl,-Bdynamic -L/usr/local/dist/linux64/lib -lOpenImageIO -lboost_system -fopenmp
INCLUDES = -I ../include/ -I /usr/local/include -I/usr/local/dist/linux64/include -I/usr/local/include
EXECUTABLE = example

all: $(EXECUTABLE)

.PHONY : $(EXECUTABLE)
$(EXECUTABLE):
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) $(LDFLAGS) -o $@

.PHONY : clean
clean:
	rm -fr $(EXECUTABLE)
