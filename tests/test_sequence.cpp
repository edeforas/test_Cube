#include <iostream>
using namespace std;

#include "Sequence.h"

int main()
{
	Sequence seq;
	seq.set_allowed_rotations("M M' U U'");
	seq.init_depth(3);

	for (int i = 0; i < 100; i++)
	{
		cout << seq.to_string(false) << endl;
		seq.next_rotation();
	}

	return 0;
}