#include "Sequence.h"
#include <cassert>
#include <sstream>

///////////////////////////////////////////////////////////////////////////////
Sequence::Sequence()
{ }
///////////////////////////////////////////////////////////////////////////////
Sequence::~Sequence()
{ }
///////////////////////////////////////////////////////////////////////////////
void Sequence::init_depth(int iDepth)
{
	_rotations.clear();
	for (int i = 0; i < iDepth; i++)
		_rotations.push_back(_allowedRotations[0]);
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::set(const vector<string>& vsSeq)
{
	_rotations = vsSeq;
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::set(const string& sSeq)
{
	split(sSeq, _rotations);
}
///////////////////////////////////////////////////////////////////////////////
const vector<string>& Sequence::rotations()
{
	return _rotations;
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::split(const string& sSeq,vector<string>& vsSeq) const
{
	vsSeq.clear();
	istringstream f(sSeq);
	string s;
	while (std::getline(f, s, ' '))
		vsSeq.push_back(s);
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::unsplit(const vector<string>& vsSeq, string& sSeq,bool bSimplify) const
{
	sSeq.clear();
	
	if (vsSeq.empty())
		return;
	
	if (!bSimplify)
		for (unsigned int i = 0; i < vsSeq.size(); i++)
			sSeq = sSeq + " " + vsSeq[i];
	else
	{
		string prevRotation="#";
		int iPrevAngle = 0; // 0 = nothing, 1= 90deg, 2 = 180deg, 3=-90deg
		for (unsigned int i = 0; i <= vsSeq.size(); i++)
		{
			if (i == 0)
				prevRotation = vsSeq[0];

			// compute current rotation and current angle
			string currentRotation;
			if (i < vsSeq.size())
				currentRotation = vsSeq[i];
			else
				currentRotation = "&"; // impossible new axis, used to add last move
			int iCurrentAngle = 0;
			if (currentRotation.size() > 1)
			{
				if (currentRotation[1] == '2') iCurrentAngle = 2;
				if (currentRotation[1] == '\'') iCurrentAngle = 3;
			}
			else
				iCurrentAngle = 1;

			if ((currentRotation[0] == prevRotation[0]))
			{
				iPrevAngle += iCurrentAngle;
			}
			else
			{
				// flush axis
				iPrevAngle = iPrevAngle % 4;
				if (iPrevAngle != 0)
				{
					if (i != 0)
						sSeq += " ";
					sSeq += prevRotation[0];
					if (iPrevAngle == 2) sSeq += "2";
					if (iPrevAngle == 3) sSeq += "'";
				}

				prevRotation = currentRotation;
				iPrevAngle = iCurrentAngle;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::set_allowed_rotations(const string& sRotations)
{
	split(sRotations, _allowedRotations);

	_nextRotation.clear();
	for (size_t i = 0; i < _allowedRotations.size(); i++)
		_nextRotation.insert({ _allowedRotations[i],_allowedRotations[(i + 1) % _allowedRotations.size()] });

	//fill next rotation on another axis
	for (size_t i = 0; i < _allowedRotations.size(); i++)
	{
		string thisRotation = _allowedRotations[i];
		string sNextRotationOtherAxis = _allowedRotations[0];
		for (size_t j = i + 1; j < _allowedRotations.size(); j++)
		{
			if (thisRotation[0] != _allowedRotations[j][0])
			{
				sNextRotationOtherAxis = _allowedRotations[j];
				break;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
bool Sequence::next_rotation() //change recent moves first
{
	if (_rotations.empty())
		return true;

	// increment the position (from the lower digit to the higher digit)
	int i=0 ;
	for (i = (int)_rotations.size()-1; i>=0; i--)
	{
		string r = _rotations[i];
		string nextRotation = _nextRotation[r];
		_rotations[i] = nextRotation;
		if (nextRotation != _allowedRotations[0]) // test if carry
			break;
	}

	return i< 0; // true if all sequence of this depth have been seen
}
///////////////////////////////////////////////////////////////////////////////
// return true if consecutive rotations does not occur on same axis
bool Sequence::is_optimised()
{
	if (_rotations.empty())
		return true;

	string r = _rotations[0];

	for (int i = 1; i < _rotations.size(); i++)
	{
		string snext = _rotations[i];

		if (r[0] == snext[0])
			return false;

		r = snext;
	}

	return true;
}
///////////////////////////////////////////////////////////////////////////////
string Sequence::to_string(bool bSimplify) const
{
	string s;
	unsplit(_rotations, s, bSimplify);
	return s;
}
///////////////////////////////////////////////////////////////////////////////
