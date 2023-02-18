#ifndef SequenceOrder_
#define SequenceOrder_

#include "Cube.h"

//compute the order of the sequence:
//  i.e. the number of sequence to apply to get back to initial state
int SequenceOrder(const string& sSequence)
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