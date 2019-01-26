EXE = exe
CXX = c++
CXXFLAGS = -Wall -Wextra -I include

all: $(EXE)

dev: include/BST.h
	$(CXX) -o $(EXE) -D__BST_DEV__ src/* main.cc $(CXXFLAGS)

$(EXE): include/BST.h
	$(CXX) -o $@ main.cc $(CXXFLAGS)

main.cc: include/BST.h

clean:
	rm -rf *~ $(EXE)

.PHONY: all dev clean
