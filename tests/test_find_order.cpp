#include <iostream>
using namespace std;

#include "SequenceOrder.h"

int main()
{
	//this code compute the number of R U movement needed to go back to identity
	
    string sSequence="R U";
    cout << "order of : " << sSequence << " is " << SequenceOrder(sSequence) << " repetitions" << endl;

    return 0;
}
