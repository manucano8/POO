EXES = test-P0-auto 
CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -pedantic
CPPFLAGS = -DP0 -I../Tests-auto -I.
VPATH = ../Tests-auto:.

CLASSES = cadena.o fecha.o


.PHONY: all clean


all: $(EXES)

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

test-fechacadena-consola: test-fechacadena-consola.o $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean: 
	@$(RM) $(EXES) *.o
