#include <iostream>
using namespace std;

#include "Cube.h"
#include "CubeHelper.h"
#include "CubeSolver.h"

// the goal is to find a Jb permutation using only L2, U, U', U2, D, D' and D2
// edges can scramble
// useful for cuboids NxNxM
// 
// it exist because there is at least one :
// https://alg.cubing.net/?type=alg&alg=U2_(L2_D-_L2_D-_L2_D2_L2_D_L2_D_L2)_U-__(L2_D-_L2_D-_L2_D2_L2_D_L2_D_L2)
int main()
{
	Cube c;
	CubeHelper::print(c);
	c.ignore_edges();
	c.rotate("R' U L' U2 R U' R' U2 R L U'"); // Jb
	CubeHelper::print(c);

	// find rotations to go back to solved state
	CubeSolver cs;
	cs.set_allowed_rotations("L2 U U' U2 D D' D2");
	cs.set_max_depth(22);
	cs.set_cube(c);
		
	cs.set_final_state(FINAL_STATE_SOLVED);
	cs.set_stop_at_first_solution(false); // find all solutions
	cs.set_output_file("test_find_Jb.txt");

	cs.run();

    return 0;
}
