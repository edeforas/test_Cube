#include <iostream>
using namespace std;

#include "Cube.h"
#include "CubeHelper.h"
#include "Sequence.h"

int main()
{
	Sequence seq;
	seq.set_allowed_rotations("M M' M2 U U' U2");
	seq.init_depth(4);

	for (int i = 0; i < 100; i++)
	{
		cout << seq.to_string(false) << endl;
		seq.next_rotation();
	}

	return 0;
}