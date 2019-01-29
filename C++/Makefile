EXE = bst_benchmark
DEV_EXE = bst_test
CXX = c++
CXXFLAGS = -Wall -Wextra -I include

.SUFFIXES:
SUFFIXES=

.SUFFIXES: .cc .x

all: $(EXE)

dev: $(DEV_EXE)

$(DEV_EXE): include/BST.h main.cc
	    $(CXX) -o $(DEV_EXE) -D__BST_DEV__ src/* main.cc $(CXXFLAGS)

$(EXE): include/BST.h main.cc
	$(CXX) -o $@ main.cc $(CXXFLAGS)

main.cc: include/BST.h

clean:
	rm -rf *~ $(EXE) $(DEV_EXE)

.PHONY: all dev clean
