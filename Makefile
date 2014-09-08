CC=clang++
CFLAGS = -std=c++11 -c -Wall -fPIC
LDFLAGS =
SOURCES=$(wildcard src/*.cpp)
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib
OPENEXR_INC = /usr/local/include
INCLUDES = -I ./include -I $(OPENEXR_INC)
LIB_VERSION = 0.1.0
OBJECTS=$(SOURCES:.cpp=.o)
GSSMRAYTRACERLIBBASENAME=libgssmraytracer
GSSMRAYTRACERSTATICLIBNAME=$(GSSMRAYTRACERLIBBASENAME).$(LIB_VERSION).a
GSSMRAYTRACERSTATICLIB=lib/$(GSSMRAYTRACERSTATICLIBNAME)
GSSMRAYTRACERSTATICSIMLIB=$(GSSMRAYTRACERLIBBASENAME).a
MKDIR_P = mkdir -p

.PHONY : makelib

all: makelib $(SOURCES) $(OBJECTS) $(GSSMRAYTRACERSTATICLIB).$(LIB_VERSION)

makelib: 
	mkdir -p lib

%.o: %.cpp
	$(CC) $(INCLUDES) -o $@ $< $(CFLAGS)

$(GSSMRAYTRACERSTATICLIB).$(LIB_VERSION): $(OBJECTS)
	ar rvs $(GSSMRAYTRACERSTATICLIB) $(OBJECTS)
	ln -f -s $(GSSMRAYTRACERLIBBASENAME).$(LIB_VERSION).a $(GSSMRAYTRACERSTATICSIMLIB)
	mv $(GSSMRAYTRACERSTATICSIMLIB) lib/$(GSSMRAYTRACERSTATICSIMLIB)

clean:
	rm -fr $(OBJECTS)
	rm -fr $(GSSMRAYTRACERSTATICLIB)
	rm -fr lib
