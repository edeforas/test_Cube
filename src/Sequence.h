#ifndef Sequence_
#define Sequence_

#include <string>
#include <vector>
#include <map>
using namespace std;

class Sequence
{
public:
	Sequence();
    ~Sequence();

	void init_depth(int iDepth);

    void set(const string& sSeq); //sSeq can be "R U' L2 " ...
	void set(const vector<string>& vsSeq);
	const vector<string>& rotations();
	string to_string(bool bSimplify=true) const;

	void set_allowed_rotations(const string& sRotations);

	bool next_rotation();

	bool is_optimised(); // does not have same consecutive same axis rotation

private:
	void split(const string& sSeq, vector<string>& vsSeq) const;
	void unsplit(const vector<string>& vsSeq, string& sSeq,bool bSimplify) const;

	vector<string> _rotations;
	vector<string> _allowedRotations;
	map<string, string> _nextRotation;
};

#endif
