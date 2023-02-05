#include "Sequence.h"
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

	// it is not possible to have the same rotation everywhere
	// the first correct sequence will be A B A B ...
	fix_same_axis();
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
	{
		vsSeq.push_back(s);
	}
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::unsplit(const vector<string>& vsSeq, string& sSeq,bool bSimplify) const
{
	sSeq.clear();
	
	if (vsSeq.empty())
		return;
	
	if (!bSimplify)
	{
		for (unsigned int i = 0; i < vsSeq.size(); i++)
			sSeq = sSeq + " " + vsSeq[i];
	}
	else
	{
		string prevRotation="#";
		int iPrevAngle = 0; // 0 = nothing, 1= direct , 2 = 180deg , 3= '
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
void Sequence::replace_inplace(string& subject, const string& search, const string& replace) const
{
	// not needed?
	// from https://stackoverflow.com/questions/1494399/how-do-i-search-find-and-replace-in-a-standard-string
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
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

		_nextRotationOtherAxis.insert({ thisRotation,sNextRotationOtherAxis });
	}
	_lastRotation = _allowedRotations[_allowedRotations.size()-1];
}
///////////////////////////////////////////////////////////////////////////////
bool Sequence::next_rotation() //change most recent moves first
{
	if (_rotations.empty())
		return true;

	// increment the position (from the lower digit to the higher digit)
	int i=0 ;
	string firstRotation = _allowedRotations[0];
	for (i = (int)_rotations.size()-1; i>=0; i--)
	{
		string r = _rotations[i];
		string nextRotation = _nextRotation[r];
		_rotations[i] = nextRotation;
		if (nextRotation != firstRotation)
			break;
	}

//	fix_same_axis();
	return i< 0; // true if all sequence of this depth done
}
///////////////////////////////////////////////////////////////////////////////
string Sequence::to_string(bool bSimplify) const
{
	string s;
	unsplit(_rotations, s, bSimplify);
	return s;
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::fix_same_axis()
{
	if (_rotations.size() <= 1)
		return;

	bool bFoundPair = true;
	while (bFoundPair)
	{
		bFoundPair = false;
		for (size_t i = 0; i < _rotations.size() - 1; i++)
		{
			string r1 = _rotations[i];
			string r2 = _rotations[i + 1];
			if ((r1[0] == r2[0]) && (r1[0]!=_lastRotation[0])) //same axis
			{
				_rotations[i + 1] = _nextRotationOtherAxis[_rotations[i + 1]];
				bFoundPair = true;
				break;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
