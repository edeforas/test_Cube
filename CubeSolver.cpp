#include <cassert>
#include <iostream>
using namespace std;

#include "CubeSolver.h"

///////////////////////////////////////////////////////////////////////////////
CubeSolver::CubeSolver()
{
	_iMaxDepth = 20;
	_bKeepFirstSolution = true;
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_allowed_rotations(string sRotations)
{
	Cube_3x3x3::split(sRotations,_allowedRotations);

	_nextRotation.clear();
	for (int i = 0; i < _allowedRotations.size(); i++)
		_nextRotation.insert({ _allowedRotations[i],_allowedRotations[(i + 1) % _allowedRotations.size()] });
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
	//test small depth first
	for (int d = 0; d <= _iMaxDepth; d++)
	{
		cout << "Searching at depth=" << d << endl;
		
		//build first small depth sequence
		vector<string> vsSequence,vsOrigSequence;
		for(int i=0 ; i<d;i++)
			vsSequence.push_back(_allowedRotations[0]);

		vsOrigSequence = vsSequence;

		do
		{ 
			Cube_3x3x3 c = _cube;

			c.rotate(vsSequence);
			if (c.is_solved())
			{
				Cube_3x3x3::unsplit(vsSequence, _sSequence);
				if(_bKeepFirstSolution)
					return true;
				else
					cout << "Found sequence: " << _sSequence << endl;
			}

			next_sequence(vsSequence);
		}
		while(vsSequence != vsOrigSequence);		
	}
	
	return false;
}
///////////////////////////////////////////////////////////////////////////////
string CubeSolver::found_sequence()
{
	return _sSequence;
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::next_sequence(vector<string>& vsSequence)
{
	int iPosRotToChange = 0;
	while (iPosRotToChange < vsSequence.size())
	{
		vsSequence[iPosRotToChange] = _nextRotation[vsSequence[iPosRotToChange]];

		if (vsSequence[iPosRotToChange] != _allowedRotations[0])
			return;
		else
			iPosRotToChange++;
	}
}
///////////////////////////////////////////////////////////////////////////////