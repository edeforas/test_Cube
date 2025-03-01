// // test is_corner_placed

#include <iostream>
using namespace std;

#include "Cube.h"
#include "CubeHelper.h"

void test(bool b,const string& sMessage = "")
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
    test(c.is_corners_placed());

    c.rotate("L U L' U L U2 L' U2"); // LSune + U2 -> rotated corners are turned but wellplaced
    test(c.is_corners_placed());

    c.init();
    c.rotate("L D L' D L D2 L' D2"); // LDownSune + D2 -> rotated corners are turned but wellplaced
    test(c.is_corners_placed());

    c.init();
    c.rotate("U"); //corner are bad placed
    test(!c.is_corners_placed());

    c.init();
    c.rotate("F"); //corner are bad placed
    test(!c.is_corners_placed());

    c.init();
    c.rotate("D"); //corner are bad placed
    test(!c.is_corners_placed());

    c.init();
    c.rotate("R"); //corner are bad placed
    test(!c.is_corners_placed());

    c.init();
    c.rotate("L"); //corner are bad placed
    test(!c.is_corners_placed());

    c.init();
    c.rotate("B"); //corner are bad placed
    test(!c.is_corners_placed());

    cout << "Test Succeded." << endl;
    return 0;
}
