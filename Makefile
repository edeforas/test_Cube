CXXFLAGS = -g -Wall -Wfatal-errors -std=c++14

ALL = test_PLL

all: $(ALL)

test_PLL: test_PLL.cpp Cube_3x3x3.cpp Makefile
	$(CXX) $(CXXFLAGS) test_PLL.cpp Cube_3x3x3.cpp -o test_PLL

clean:
	$(RM) $(ALL) *.o

test: all
	./test_PLL
