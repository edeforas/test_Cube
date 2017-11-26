#ifndef Period_
#define Period_

#include "Cube.h"

//compute the period (or order) of the sequence:
//  i.e. the number of sequence to apply to get back to initial state
int Period(const string& sSequence)
{
    Cube c;
    int iNB=0;

    do
    {
        c.rotate(sSequence);
        iNB++;
    }
    while(!c.is_solved());

    return iNB;
}
#endif