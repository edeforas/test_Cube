#include <iostream>
using namespace std;

#include "Cube.h"
#include "CubeHelper.h"
#include "CubeSolver.h"

// the goal is to find a Jb permutation on a RUF constrained cube (only move on F, R and U allowed)
// using only F F' R R' U U'
// corners will we turned later using Sune
// edges can scramble, will be solved later using U perm

void test(bool b, const string& sMessage = "")
{
	if (!b)
	{
		cerr << "Test Error: " << sMessage.c_str() << endl;
		exit(-1);
	}
}

int main()
{
	Cube c;
	CubeHelper::print(c);
	c.ignore_edges();
	c.rotate("R' U L' U2 R U' R' U2 R L U'"); // Jb setup
	CubeHelper::print(c);

	// find rotations to go back to solved state
	CubeSolver cs;
	cs.set_allowed_rotations("F F' R R' U U'");
	cs.set_max_depth(9);
	cs.set_cube(c);
		
	cs.set_final_state(FINAL_STATE_CORNERPLACED);
	cs.set_stop_at_first_solution(false); // find all solutions
	cs.set_output_file("test_find_Jb_3faces_RUF.txt");

	test(cs.run());

    return 0;
}
