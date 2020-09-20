#ifndef CubeSolver_
#define CubeSolver_

#include <string>
#include <map>
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
	void set_keep_first_solution(bool bKeepFirstSolution);

	bool run(); //return true if solution found

	string found_sequence();

private:
	void next_sequence(vector<string>& vsSequence);

	vector<string> _allowedRotations;
	long _iMaxDepth;
	bool _bKeepFirstSolution;
	string _sSequence;
	Cube_3x3x3 _cube;
	map<string, string> _nextRotation;
};

#endif
