#include <iostream>
using namespace std;

#include "Cube.h"

namespace CubeHelper
{
    unsigned char color(int i)
    {
        if (i == WHITE) return 'W';
        if (i == YELLOW) return 'Y';
        if (i == RED) return 'R';
        if (i == ORANGE) return 'O';
        if (i == BLUE) return 'B';
        if (i == GREEN) return 'G';
        if (i == GREY) return 'x';

        return '?';
    }

    void print(Cube& c)
    {
        //format is  B
        //format is LUR
        //format is  F
        //format is  D

        //index is     812
        //index is     703
        //index is     654

        //index is 812 812 812
        //index is 703 703 703
        //index is 654 654 654

        //index is     812
        //index is     703
        //index is     654

        //index is     812
        //index is     703
        //index is     654

        auto R = c.faceR();
        auto L = c.faceL();
        auto U = c.faceU();
        auto F = c.faceF();
        auto D = c.faceD();
        auto B = c.faceB();

        cout << "    " << color(B.facet(8)) << color(B.facet(1)) << color(B.facet(2)) << endl;
        cout << "    " << color(B.facet(7)) << color(B.facet(0)) << color(B.facet(3)) << endl;
        cout << "    " << color(B.facet(6)) << color(B.facet(5)) << color(B.facet(4)) << endl;
        cout << endl;

        cout << color(L.facet(8)) << color(L.facet(1)) << color(L.facet(2)) << " " << color(U.facet(8)) << color(U.facet(1)) << color(U.facet(2)) << " " << color(R.facet(8)) << color(R.facet(1)) << color(R.facet(2)) << endl;
        cout << color(L.facet(7)) << color(L.facet(0)) << color(L.facet(3)) << " " << color(U.facet(7)) << color(U.facet(0)) << color(U.facet(3)) << " " << color(R.facet(7)) << color(R.facet(0)) << color(R.facet(3)) << endl;
        cout << color(L.facet(6)) << color(L.facet(5)) << color(L.facet(4)) << " " << color(U.facet(6)) << color(U.facet(5)) << color(U.facet(4)) << " " << color(R.facet(6)) << color(R.facet(5)) << color(R.facet(4)) << endl;
        cout << endl;

        cout << "    " << color(F.facet(8)) << color(F.facet(1)) << color(F.facet(2)) << endl;
        cout << "    " << color(F.facet(7)) << color(F.facet(0)) << color(F.facet(3)) << endl;
        cout << "    " << color(F.facet(6)) << color(F.facet(5)) << color(F.facet(4)) << endl;
        cout << endl;

        cout << "    " << color(D.facet(8)) << color(D.facet(1)) << color(D.facet(2)) << endl;
        cout << "    " << color(D.facet(7)) << color(D.facet(0)) << color(D.facet(3)) << endl;
        cout << "    " << color(D.facet(6)) << color(D.facet(5)) << color(D.facet(4)) << endl;
        cout << endl;
    }
}