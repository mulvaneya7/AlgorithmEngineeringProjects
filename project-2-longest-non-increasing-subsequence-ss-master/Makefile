
GXX49_VERSION := $(shell g++-4.9 --version 2>/dev/null)

ifdef GXX49_VERSION
	CXX_COMMAND := g++-4.9
else
	CXX_COMMAND := g++
endif

CXX = ${CXX_COMMAND} -std=c++14 -Wall

all: subsequence_timing run_test

run_test: subsequence_test
	./subsequence_test

headers: rubrictest.hpp subsequence.hpp timer.hpp

subsequence_test: headers subsequence_test.cpp
	${CXX} subsequence_test.cpp -o subsequence_test

subsequence_timing: headers subsequence_timing.cpp
	${CXX} subsequence_timing.cpp -o subsequence_timing

clean:
	rm -f subsequence_test subsequence_timing
