#ifndef Sequence_
#define Sequence_

#include <string>
#include <vector>
#include <map>
using namespace std;

#define ROT_U (256+1)
#define ROT_Up (256*2+1)
#define ROT_U2 (256*3+1)

#define ROT_R (256+2)
#define ROT_Rp (256*2+2)
#define ROT_R2 (256*3+2)

#define ROT_L (256+4)
#define ROT_Lp (256*2+4)
#define ROT_L2 (256*3+4)

#define ROT_F (256+8)
#define ROT_Fp (256*2+8)
#define ROT_F2 (256*3+8)

#define ROT_D (256+16)
#define ROT_Dp (256*2+16)
#define ROT_D2 (256*3+16)

#define ROT_B (256+32)
#define ROT_Bp (256*2+32)
#define ROT_B2 (256*3+32)

#define ROT_M (256+64)
#define ROT_Mp (256*2+64)
#define ROT_M2 (256*3+64)

#define ROT_SAME_AXIS(a,b) (((a & b) & 255)!=0)

class Sequence
{
public:
	Sequence();
    ~Sequence();

	void init_depth(int iDepth);

    void set(const string& sSeq); //sSeq can be "R U' L2 " ...
	void set(const vector<int>& vsSeq);
	const vector<int>& rotations();
	string to_string(bool bSimplify=true) const;

	void set_allowed_rotations(const string& sRotations);

	bool next_rotation();

	bool is_optimised(); // does not have same consecutive same axis rotation

private:
	void from_string(const string& sSeq, vector<int>& vsSeq) const;
	void to_string(const vector<int>& vsSeq, string& sSeq,bool bSimplify) const;
	void build_map_fromto_string();

	map<string, int> _mapFromString;
	map<int, string> _mapToString;

	vector<int> _rotations;
	vector<int> _allowedRotations;
	map<int, int> _nextRotation;
};

#endif
