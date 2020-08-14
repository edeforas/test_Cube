#include <cassert>
#include <iostream>
using namespace std;

#include "CubeSolver.h"

///////////////////////////////////////////////////////////////////////////////
CubeSolver::CubeSolver()
{
	_iMaxDepth = 20;
	_iDepth = 0;
	_iNbTested = 0;
	_bKeepFirstSolution = true;
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_allowed_rotations(string sRotations)
{
	Cube_3x3x3::split(sRotations,_allowedRotations);
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_max_depth(int iMaxDepth)
{
	_iMaxDepth = iMaxDepth;
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_cube(Cube_3x3x3& cube)
{
	_cube = cube;
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_keep_first_solution(bool bKeepFirstSolution)
{
	_bKeepFirstSolution = bKeepFirstSolution;
}
///////////////////////////////////////////////////////////////////////////////
bool CubeSolver::run()
{
	_iDepth = 0;
	_iNbTested = 0;
	return iterate();
}
///////////////////////////////////////////////////////////////////////////////
string CubeSolver::found_sequence()
{
	return _sSequence;
}
///////////////////////////////////////////////////////////////////////////////
bool CubeSolver::iterate()
{
	//lots of recursive call ; bad! but call depth is small (<50)

	if (_cube.is_solved())
		return true;
	
	if (_iDepth == _iMaxDepth)
		return false;
	_iDepth++;

	if (_iNbTested % (1'000'000L) == 0L)
		cout << _sSequence << "***** nbTested=" << _iNbTested << endl;
	
	Cube_3x3x3 cubeOld = _cube;
	string sSequenceOld = _sSequence;
	for (int i = 0; i < _allowedRotations.size(); i++)
	{
		_sSequence = sSequenceOld + " " + _allowedRotations[i];
		_cube = cubeOld;
		_cube.rotate(_allowedRotations[i]);
		if (iterate() && _bKeepFirstSolution)
			return true;
		
		_iNbTested++;
	}

	_sSequence = sSequenceOld;
	_iDepth--;
	_cube = cubeOld;

	return false;
}
///////////////////////////////////////////////////////////////////////////////



