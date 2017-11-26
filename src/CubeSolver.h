#ifndef CubeSolver_
#define CubeSolver_

#include <string>
using namespace std;

#include "Cube.h"
#include "Sequence.h"

class CubeSolver
{
public:
	CubeSolver();
	void set_cube(const Cube& cube);
	void set_allowed_rotations(const string& sAllowedRotations);
	void set_max_depth(int iMaxDepth);
	void set_stop_at_first_solution(bool bStopAtFirstSolution);
	void set_final_state_pll(bool bFinalStatePLL);
	void set_output_file(const string& sFile);

	bool run(); //return true if solution found

	string found_sequence();

private:
	long _iMaxDepth;
	bool _bStopAtFirstSolution;
	Cube _cube;
	bool _bFinalStatePLL; // if true: a PLL is a valid solution else use solved state
	string _sFileAllSolutions;
	Sequence _seq;
};

#endif
