#include <iostream>
using namespace std;

#include "Period.h"

int main()
{
	//this code compute the number of RUL movement needed to go back to identity
	
    string sSequence="RUL'";
    cout << "period of : " << sSequence << " is " << Period(sSequence) << " repetitions" << endl;

    return 0;
}
