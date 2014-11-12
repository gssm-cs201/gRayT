CC=g++
CFLAGS  = -c -fPIC -std=c++11
LDFLAGS = -L ../lib/ -lgssmraytracer -lglut -lGL -lGLU -lm -L/usr/local/lib -lImath -lIex -L/usr/local/dist/linux64/lib -lOpenImageIO -lboost_system -fopenmp
INCLUDES = -I../include/ -I/usr/local/include -I/usr/local/dist/linux64/include -I/usr/local/include -I/usr/include/python2.7
MODULE = _grayt.so

all: $(MODULE)

.PHONY : $(MODULE)

$(MODULE):
	swig $(INCLUDES) -c++ -python gssmraytracer.i
	g++ -fPIC -c -L../lib -lgssmraytracer gssmraytracer_wrap.cxx -I/usr/include/python2.7 -I../include -std=c++11
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS)
	$(CC) -shared gssmraytracer_wrap.o $(LDFLAGS) -o $@

.PHONY : clean
clean:
	rm -fr $(MODULE)
	rm -fr grayt.py
	rm -fr gssmraytracer_wrap.cxx
	rm -fr gssmraytracer_wrap.o




#swig -I../include -c++ -python gssmraytracer.i
#g++ -fPIC -c -L../lib -lgssmraytracer gssmraytracer_wrap.cxx -I/usr/include/python2.7 -I../include -std=c++11
#g++ -shared gssmraytracer_wrap.o -L../lib -l gssmraytracer -o _grayt.so
