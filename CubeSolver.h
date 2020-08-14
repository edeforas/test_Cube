#ifndef CubeSolver_
#define CubeSolver_

#include <string>
#include <vector>
using namespace std;

#include "Cube_3x3x3.h"

class CubeSolver
{
public:
	CubeSolver();
	void set_allowed_rotations(string sRotations);
	void set_max_depth(int iMaxDepth);
	void set_cube(Cube_3x3x3& cube);

	bool run(); //return true if solution found

	string found_sequence();

private:
	vector<string> _allowedRotations;
	int _iMaxDepth;
	string _sFoundSequence;
	Cube_3x3x3 _cube;

};

#endif
