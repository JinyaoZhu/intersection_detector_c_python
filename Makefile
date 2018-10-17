_example.so : example.o example_wrap.o
	gcc -shared example.o example_wrap.o -o _example.so -lpython3.5m

example.o : example.cxx
	gcc -c -fPIC -I/usr/include/python3.5m example.cxx

example_wrap.o : example_wrap.cxx
	gcc -c -fPIC -I/usr/include/python3.5m example_wrap.cxx

example_wrap.cxx example.py : example.i example.h
	swig  -c++ -python  example.i

clean:
	rm -f *.o *.so example_wrap.* example.py*

test:
	python3 test.py

all: clean _example.so test
 
.PHONY: clean test all

.DEFAULT_GOAL := all