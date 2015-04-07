CC=clang++ 
SOURCE = test.cpp 
INCLUDE = -I ../include
LIB = -L ../lib -lgrayt -L /usr/lib64/ -lgtest
EXE = runtests

all: $(EXE)

.PHONY: $(EXE)
$(EXE): 
	$(CC) $(SOURCE) $(INCLUDE) $(LIB) -o $@

clean:
	rm -fr $(EXE)
