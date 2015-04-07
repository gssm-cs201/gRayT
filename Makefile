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
graytLIBBASENAME=libgrayt
graytSTATICLIBNAME=$(graytLIBBASENAME).$(LIB_VERSION).a
graytSTATICLIB=lib/$(graytSTATICLIBNAME)
graytSTATICSIMLIB=$(graytLIBBASENAME).a
MKDIR_P = mkdir -p

.PHONY : makelib makedocs docs

all: makelib makedocs $(SOURCES) $(OBJECTS) $(graytSTATICLIB).$(LIB_VERSION)

makelib:
	mkdir -p lib

makedocs:
	mkdir -p docs

%.o: %.cpp
	$(CC) $(INCLUDES) -o $@ $< $(CFLAGS)

$(graytSTATICLIB).$(LIB_VERSION): $(OBJECTS)
	ar rvs $(graytSTATICLIB) $(OBJECTS)
	ln -f -s $(graytLIBBASENAME).$(LIB_VERSION).a $(graytSTATICSIMLIB)
	mv $(graytSTATICSIMLIB) lib/$(graytSTATICSIMLIB)

docs:
	cd docs;doxygen Doxyfile
clean:
	rm -fr $(OBJECTS)
	rm -fr $(graytSTATICLIB)
	rm -fr lib
	rm -fr docs/html
	rm -fr docs/latex
