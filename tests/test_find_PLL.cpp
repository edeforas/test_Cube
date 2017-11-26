#include <iostream>
using namespace std;

#include "Cube.h"
#include "CubeHelper.h"
#include "CubeSolver.h"

// the goal is to find all pll that use R, U, F or L
// valid final position is 
// the yellow and white face solved and two first layers solved (PLL ready)

int main()
{
	// cube is in solved state
	Cube c;
	disp(c);

	// find rotations to go back to PLL state
	CubeSolver cs;
	cs.set_allowed_rotations("U U' U2 R R' R2 L L' L2 F F' F2");
	cs.set_max_depth(12);
	cs.set_cube(c);
	cs.set_final_state_pll(true); // accept all non trivial PLL positions
	cs.set_stop_at_first_solution(false); // disp all solutions
	cs.set_output_file("test_find_PLL.txt");

	cs.run();

    return 0;
}
