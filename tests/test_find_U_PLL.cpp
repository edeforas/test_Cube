#include <iostream>
using namespace std;

#include "Cube.h"
#include "CubeHelper.h"
#include "CubeSolver.h"

// the goal is to find an U permutation using only L2, U, U' and U2

// it exist because there is at least one : U' (L2 U2)3 L2 U L2 U' (L2 U2)3 U L2 U' L2 U as in 
// https://alg.cubing.net/?stage=PLL&type=alg&setup=_U-_(L2_U2)3_L2_U_L2_U-_(L2_U2)3_U_L2_U-_L2U
// but is this sequence minimal ? (22h, 38q)

// spoil : this one can be found :(17h, 28q)
//https://alg.cubing.net/?type=alg&alg=(U_R2)3_(U2_R2)2_(U_R2)2_(U2_R2)_U

int main()
{
	Cube c;
	CubeHelper::print(c);
	c.rotate("M2 U M' U2 M U M2"); // U Permutation  as in https://alg.cubing.net/?stage=PLL&type=alg&view=playback&alg=M2_U_M-_U2_M_U_M2

	// find rotations to go back to solved state
	CubeSolver cs;
	cs.set_allowed_rotations("L2 U U' U2");
	cs.set_max_depth(22);
	cs.set_cube(c);
		
	cs.set_final_state(FINAL_STATE_SOLVED);
	cs.set_stop_at_first_solution(false); // find all solutions
	cs.set_output_file("test_find_U_PLL.txt");

	cs.run();

    return 0;
}
