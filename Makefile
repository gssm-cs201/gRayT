CC=clang++
CFLAGS = -std=c++11 -c -Wall -fPIC
LDFLAGS =
SOURCES=$(wildcard src/*.cpp)
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib
OPENEXR_INC = /usr/local/include
INCLUDES = -I ./include -I $(OPENEXR_INC)
LIB_VERSION = "0.1.0"
OBJECTS=$(SOURCES:.cpp=.o)
GSSMRAYTRACERSTATICLIBNAME=libgssmraytracer.a
GSSMRAYTRACERSTATICLIB=lib/$(GSSMRAYTRACERSTATICLIBNAME)

all: $(SOURCES) $(OBJECTS) $(GSSMRAYTRACERSTATICLIB).$(LIB_VERSION)
%.o: %.cpp
	$(CC) $(INCLUDES) -o $@ $< $(CFLAGS)

$(GSSMRAYTRACERSTATICLIB).$(LIB_VERSION): $(OBJECTS)
	ar rvs $(GSSMRAYTRACERSTATICLIB) $(OBJECTS)

clean:
	rm -fr $(OBJECTS)
	rm -fr $(GSSMRAYTRACERSTATICLIB)
