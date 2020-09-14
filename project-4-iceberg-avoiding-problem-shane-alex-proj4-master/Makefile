
CXX = g++ -std=c++17 -Wall

all: run_test ices_timing

run_test: ices_test
	./ices_test

headers: rubrictest.hpp ices_types.hpp ices_algs.hpp

ices_test: headers ices_test.cpp
	${CXX} ices_test.cpp -o ices_test

ices_timing: headers ices_timing.cpp
	${CXX} ices_timing.cpp -o ices_timing

clean:
	rm -f ices_test ices_timing
