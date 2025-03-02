#include "Sequence.h"
#include <cassert>
#include <sstream>

///////////////////////////////////////////////////////////////////////////////
Sequence::Sequence()
{ 
	build_map_fromto_string();
}
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
void Sequence::set(const vector<int>& vsSeq)
{
	_rotations = vsSeq;
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::set(const string& sSeq)
{
	from_string(sSeq, _rotations);
}
///////////////////////////////////////////////////////////////////////////////
const vector<int>& Sequence::rotations()
{
	return _rotations;
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::from_string(const string& sSeq,vector<int>& vsSeq) const
{
	vsSeq.clear();
	istringstream f(sSeq);
	string s;
	while (std::getline(f, s, ' '))
	{
		auto it = _mapFromString.find(s);
		if (it != _mapFromString.end())
			vsSeq.push_back((it->second));
		else
			throw("Unknow rotation" + s);
	}
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::to_string(const vector<int>& vsSeq, string& sSeq,bool bSimplify) const
{
	(void)bSimplify;
	sSeq.clear();
	for (auto& s:vsSeq)
		sSeq += " "+ _mapToString.at(s);
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::set_allowed_rotations(const string& sRotations)
{
	from_string(sRotations, _allowedRotations);

	_nextRotation.clear();
	for (size_t i = 0; i < _allowedRotations.size(); i++)
		_nextRotation.insert({ _allowedRotations[i],_allowedRotations[(i + 1) % _allowedRotations.size()] });

	//fill next rotation on another axis
	for (size_t i = 0; i < _allowedRotations.size(); i++)
	{
		int thisRotation = _allowedRotations[i];
		int sNextRotationOtherAxis = _allowedRotations[0];
		for (size_t j = i + 1; j < _allowedRotations.size(); j++)
		{
			if (ROT_SAME_AXIS(thisRotation, _allowedRotations[j])==false)
			{
				sNextRotationOtherAxis = _allowedRotations[j];
				break;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
bool Sequence::next_rotation() //change recent moves first , return true if all possible rotations has been seen
{
	int iSize = (int)_rotations.size();
	if (iSize==0)
		return true;

	// increment the position (from the lower digit to the higher digit)
	int i=0;
	for (i = iSize-1; i>=0; i--)
	{
		int r = _rotations[i];
		int nextRotation = _nextRotation[r];
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
	auto iSize = _rotations.size();
	if (iSize<2)
		return true;

	int r = _rotations[0];

	for (size_t i = 1; i < iSize; i++)
	{
		int snext = _rotations[i];

		if (ROT_SAME_AXIS(r, snext))
			return false;

		r = snext;
	}

	return true;
}
///////////////////////////////////////////////////////////////////////////////
string Sequence::to_string(bool bSimplify) const
{
	string s;
	to_string(_rotations, s, bSimplify);
	return s;
}
///////////////////////////////////////////////////////////////////////////////
void Sequence::build_map_fromto_string()
{
	_mapFromString.clear();
	_mapFromString["U"] = ROT_U;
	_mapFromString["U'"] = ROT_Up;
	_mapFromString["U2"] = ROT_U2;

	_mapFromString["L"] = ROT_L;
	_mapFromString["L'"] = ROT_Lp;
	_mapFromString["L2"] = ROT_L2;

	_mapFromString["R"] = ROT_R;
	_mapFromString["R'"] = ROT_Rp;
	_mapFromString["R2"] = ROT_R2;

	_mapFromString["F"] = ROT_F;
	_mapFromString["F'"] = ROT_Fp;
	_mapFromString["F2"] = ROT_F2;

	_mapFromString["D"] = ROT_D;
	_mapFromString["D'"] = ROT_Dp;
	_mapFromString["D2"] = ROT_D2;

	_mapFromString["B"] = ROT_B;
	_mapFromString["B'"] = ROT_Bp;
	_mapFromString["B2"] = ROT_B2;

	_mapFromString["M"] = ROT_M;
	_mapFromString["M'"] = ROT_Mp;
	_mapFromString["M2"] = ROT_M2;

	_mapFromString["X"] = ROT_X;
	_mapFromString["X'"] = ROT_Xp;
	_mapFromString["X2"] = ROT_X2;

	_mapToString.clear();
	for (auto& it:_mapFromString)
		_mapToString[it.second] = it.first;
}
///////////////////////////////////////////////////////////////////////////////