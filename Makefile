CXXFLAGS = -g -Wall -Wfatal-errors -std=c++17

ALL = test_PLL test_Period

all: $(ALL)

test_PLL: test_PLL.cpp Cube_3x3x3.cpp Makefile
	$(CXX) $(CXXFLAGS) test_PLL.cpp Cube_3x3x3.cpp -o test_PLL

test_Period: test_Period.cpp Cube_3x3x3.cpp Makefile
	$(CXX) $(CXXFLAGS) test_Period.cpp Cube_3x3x3.cpp -o test_Period

clean:
	$(RM) $(ALL) *.o

test: all
	./test_PLL && ./test_Period
	
