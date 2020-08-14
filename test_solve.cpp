#include <iostream>
using namespace std;

#include "Cube_3x3x3.h"
#include "CubeHelper.h"
#include "CubeSolver.h"


// the goal of this test is to find a movement that swap two up corners using only U, R2 and D
// all edge ignored (this is for masterball or 2x2 cube)
// this movement can be used to solve the Masterball cube : https://www.jaapsch.net/puzzles/master.htm

int main()
{
    Cube_3x3x3 c;
	
	//set the cube in final state
	c.rotate("R'UL' U2 RU'R' U2 RLU'"); //exchange 2 far corners PLL
    disp(c);
	c.ignore_edge();

	//now find movements to go back to solved state 
	CubeSolver cs;
	cs.set_allowed_rotations("U R2 D");
	cs.set_max_depth(15);
	cs.set_cube(c);

	if (cs.run())
		cout << "Solution found, final sequence is: " << cs.found_sequence() << endl;
	else
		cout << "Solution not found !" << endl;

    return 0;
}
