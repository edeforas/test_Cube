#ifndef CubeSolver_
#define CubeSolver_

#include <string>
using namespace std;

#include "Cube.h"
#include "Sequence.h"

#define FINAL_STATE_SOLVED (0) //solved
#define FINAL_STATE_PLL (1) // edge and corner need PLL
#define FINAL_STATE_EDGEPLL (2) // corners are well placed, edge need PLL
#define FINAL_STATE_CORNERPLACED (3) // corners are well placed, but may need rorientating, edge anywhere

class CubeSolver
{
public:
	CubeSolver();
	void set_cube(const Cube& cube);
	void set_allowed_rotations(const string& sAllowedRotations);
	void set_max_depth(int iMaxDepth);
	void set_stop_at_first_solution(bool bStopAtFirstSolution);
	void set_final_state(int iFinalState);
	void set_output_file(const string& sFile);

	bool run(); //return true if solution found

	string found_sequence();

private:
	long _iMaxDepth;
	bool _bStopAtFirstSolution;
	Cube _cube;
	bool _bFinalStatePLL; // if true: a PLL is a valid solution else use solved state
	bool _bCornerSolved; // if true, solve edge now
	string _sFileAllSolutions;
	int _iFinalState;
	Sequence _seq;
};

#endif
