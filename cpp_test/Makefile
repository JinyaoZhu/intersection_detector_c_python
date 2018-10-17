_interdection_detector.so : interdection_detector.o interdection_detector_wrap.o
	g++ -shared interdection_detector.o interdection_detector_wrap.o -o _interdection_detector.so -lpython3.5m

interdection_detector.o : interdection_detector.cxx
	g++ -c -fPIC -I/usr/include/python3.5m interdection_detector.cxx

interdection_detector_wrap.o : interdection_detector_wrap.cxx
	g++ -c -fPIC -I/usr/include/python3.5m interdection_detector_wrap.cxx

interdection_detector_wrap.cxx interdection_detector.py : interdection_detector.i interdection_detector.h
	swig  -c++ -python  interdection_detector.i

clean:
	rm -f *.o *.so interdection_detector_wrap.* interdection_detector.py*

test:
	python3 test.py

all: clean _interdection_detector.so test
 
.PHONY: clean test all

.DEFAULT_GOAL := all