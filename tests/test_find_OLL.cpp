#include <iostream>
using namespace std;

#include "Cube.h"
#include "CubeHelper.h"
#include "CubeSolver.h"

// the goal of this test is to find all edge rotations using M rotations

int main()
{
	Cube c;

	//set the cube in final state:
	
	//OLL28: rotate two edges R-U and F-U
	// https://alg.cubing.net/?stage=OLL&type=alg&view=playback&alg=M_U_M-_U2_M_U_M-
	c.rotate("M U M' U2 M U M'");

	//OLL57 rotate two edges F-U and B-U
	// https://alg.cubing.net/?stage=OLL&type=alg&view=playback&alg=M-_U_M-_U_M-_U_M-_U2_M-_U_M-_U_M-_U_M- 
	//c.rotate(" M' U M' U M' U M' U2 M' U M' U M' U M'");
	
	//OLL20 rotate four edge
	// https://alg.cubing.net/?stage=OLL&type=alg&view=playback&alg=r_U_R-_U-_M2_U_R_U-_R-_U-_M-
	//c.rotate("r U R' U' M2 U R U' R' U' M'");

	CubeHelper::print(c);

	//now find movements to go back to solved state
	CubeSolver cs;
	cs.set_allowed_rotations("M M' M2 U U' U2");
	cs.set_max_depth(20);
	cs.set_final_state(true); // accept PLL state for solution
	cs.set_cube(c);
	cs.set_stop_at_first_solution(false);
	cs.set_output_file("test_find_OLL28.txt");
	
	cs.run();

	return 0;
}