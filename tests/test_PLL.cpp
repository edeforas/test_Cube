// simple test with two corner swaping PLL

#include <iostream>
using namespace std;

#include "Cube.h"
#include "CubeHelper.h"

void test(bool b, const string& sMessage = "")
{
    if (!b)
    {
        cerr << "Test Error: " << sMessage.c_str() << endl;
        exit(-1);
    }
}

int main()
{
    Cube c;
    c.rotate("R' U L' U2 R U' R' U2 R L U'"); //exchange 2 far corners PLL
    CubeHelper::print(c);
    cout << "solved?:" << c.is_solved() << " pll_state?:" << c.is_pll_state() << endl << endl;

    test(!c.is_solved());
    test(c.is_pll_state());
    test(!c.is_corners_placed());

    cout << "Test Succeded." << endl;
    return 0;
}
