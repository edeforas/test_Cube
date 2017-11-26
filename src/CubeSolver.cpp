#include "CubeSolver.h"
#include <cassert>
#include <iostream>
#include <set>
#include <fstream>
using namespace std;

#include "CubeSolver.h"

///////////////////////////////////////////////////////////////////////////////
CubeSolver::CubeSolver()
{
	_iMaxDepth = 20;
	_bStopAtFirstSolution = true;
	_bFinalStatePLL = false; // todo add accessor
	_sFileAllSolutions="";
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_allowed_rotations(const string& sAllowedRotations)
{
	_seq.set_allowed_rotations(sAllowedRotations);
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_max_depth(int iMaxDepth)
{
	_iMaxDepth = iMaxDepth;
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_cube(const Cube& cube)
{
	_cube = cube;
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_stop_at_first_solution(bool bStopAtFirstSolution)
{
	_bStopAtFirstSolution = bStopAtFirstSolution;
}
///////////////////////////////////////////////////////////////////////////////
bool CubeSolver::run()
{
	std::ofstream f(_sFileAllSolutions);
	set<string> uniqueSolutions;

	// for all depths
	for (int depth = 0; depth <= _iMaxDepth; depth++)
	{
		bool bGrowSequence = false;
		cout << "Searching at depth=" << depth << endl;
		_seq.init(depth);

		do
		{ 			
			Cube c = _cube;
			c.rotate(_seq.rotations());

			bool bFoundSolution = false;
			if (_bFinalStatePLL)
				bFoundSolution = c.is_pll_state();
			else
				bFoundSolution = c.is_solved();

			if (bFoundSolution)
			{
				if (_bStopAtFirstSolution)
					return true;
				else
				{
					string s = _seq.to_string();
					cout << "Found sequence: " << s << endl;
					if (!_sFileAllSolutions.empty())
					{
						if (uniqueSolutions.count(s) == 0)
						{
							uniqueSolutions.insert(s);
							f << s << endl;
						}
					}
				}
			}
			
			bGrowSequence=_seq.next_rotation();
		} while (!bGrowSequence);
	}
	
	return false;
}
///////////////////////////////////////////////////////////////////////////////
string CubeSolver::found_sequence()
{
	return _seq.to_string();
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_final_state_pll(bool bFinalValidPLL)
{
	_bFinalStatePLL = bFinalValidPLL;
}
///////////////////////////////////////////////////////////////////////////////
void CubeSolver::set_output_file(const string& sFileAllSolutions)
{
	_sFileAllSolutions = sFileAllSolutions;
}
///////////////////////////////////////////////////////////////////////////////