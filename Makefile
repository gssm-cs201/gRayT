CC=g++
CFLAGS = -std=c++11 -c -Wall -fPIC -g -fopenmp
LDFLAGS =
LIBS = -L /usr/local/lib -lImath -lIex -L/usr/local/dist/linux64/lib -lOpenImageIO -fopenmp
SOURCES=$(wildcard src/*.cpp)
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib
OPENEXR_INC = /usr/local/include
INCLUDES = -I ./include -I $(OPENEXR_INC) -I/usr/local/dist/linux64/include -I/usr/local/include 
LIB_VERSION = 0.1.0
OBJECTS=$(SOURCES:.cpp=.o)
GSSMRAYTRACERLIBBASENAME=libgssmraytracer
GSSMRAYTRACERSTATICLIBNAME=$(GSSMRAYTRACERLIBBASENAME).$(LIB_VERSION).a
GSSMRAYTRACERSTATICLIB=lib/$(GSSMRAYTRACERSTATICLIBNAME)
GSSMRAYTRACERSTATICSIMLIB=$(GSSMRAYTRACERLIBBASENAME).a
MKDIR_P = mkdir -p

.PHONY : makelib makedocs docs

all: makelib makedocs $(SOURCES) $(OBJECTS) $(GSSMRAYTRACERSTATICLIB).$(LIB_VERSION)

makelib:
	mkdir -p lib

makedocs:
	mkdir -p docs

%.o: %.cpp
	$(CC) $(INCLUDES) -o $@ $< $(CFLAGS)

$(GSSMRAYTRACERSTATICLIB).$(LIB_VERSION): $(OBJECTS)
	ar rvs $(GSSMRAYTRACERSTATICLIB) $(OBJECTS)
	ln -f -s $(GSSMRAYTRACERLIBBASENAME).$(LIB_VERSION).a $(GSSMRAYTRACERSTATICSIMLIB)
	mv $(GSSMRAYTRACERSTATICSIMLIB) lib/$(GSSMRAYTRACERSTATICSIMLIB)

docs:
	cd docs;doxygen Doxyfile
clean:
	rm -fr $(OBJECTS)
	rm -fr $(GSSMRAYTRACERSTATICLIB)
	rm -fr lib
	rm -fr docs/html
	rm -fr docs/latex
