#include <iostream>
using namespace std;

#include "Period.h"

int main()
{
	//this code compute the number of RUR'U' movement needed to go back to identity
	
    string sSequence="RUR'U'";
    cout << "period of : " << sSequence << " is " << Period(sSequence) << " repetitions" << endl;

    return 0;
}
