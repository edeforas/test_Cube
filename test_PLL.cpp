#include <iostream>
using namespace std;

#include "Cube_3x3x3.h"
#include "CubeHelper.h"

int main()
{
    Cube_3x3x3 c;
    c.rotate("R'UL' U2 RU'R' U2 RLU'"); //exchange 2 far corners PLL
    disp(c);
    cout << "solved?:" << c.is_solved() << " pll_state?:" << c.is_ready_for_pll() << endl << endl;

    return 0;
}
