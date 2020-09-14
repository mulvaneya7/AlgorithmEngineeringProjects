
GXX49_VERSION := $(shell g++-4.9 --version 2>/dev/null)

ifdef GXX49_VERSION
	CXX_COMMAND := g++-4.9
else
	CXX_COMMAND := g++
endif

CXX = ${CXX_COMMAND} -std=c++14 -Wall

all: run_test

run_test: cuckoo
	./cuckoo

cuckoo: cuckoo.cxx
	${CXX} cuckoo.cxx -o cuckoo
 
clean:
	rm -f cuckoo