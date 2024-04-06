#include <iostream>
using namespace std;

#include "Sequence.h"

int main()
{
	// test if cycling with Sequence go thru all possibles moves 
	Sequence seq;
	seq.set_allowed_rotations("M M' U U'");
	seq.init_depth(3);

	for (int i = 0; i < 100; i++)
	{
		cout << seq.to_string(false) << endl;
		bool newCycle=seq.next_rotation();
		if (newCycle )
			cout << "newCycle!" << endl;
	}

	return 0;
}