CXXFLAGS = -g -Wall -Wfatal-errors -std=c++14

ALL = test_PLL

all: $(ALL)

hello: test_PLL.cpp Cube_3x3x3.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp

clean:
	$(RM) $(ALL) *.o

test: all
	bash test_PLL
