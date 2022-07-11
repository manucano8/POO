CXX = clang++
CPPFLAGS = -DP1 -I../Tests-auto -I.
CXXFLAGS = -std=c++17 -Wall -pedantic -g
VPATH = ../Tests-auto:.

all: test-fechacadena-consola test-P1-auto

test-fechacadena-consola: test-fechacadena-consola.o fecha.o cadena.o
	@${CXX} -o $@ ${LDFLAGS} $^

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o
	@${CXX} -o $@ ${LDFLAGS} $^

test-caso0-fecha-auto.o test-caso0-cadena-auto.o: test-auto.hpp fecha.hpp cadena.hpp fct.h

cadena.o: cadena.hpp

fecha.o: fecha.hpp

test-fechacadena-consola.o: cadena.hpp fecha.hpp

clean:

	@${RM} test-fechacadena-consola test-P1-auto *.o
