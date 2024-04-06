#include "Cube.h"
#include <cassert>
#include "Sequence.h"

// cube notations at: https://jperm.net/3x3/moves

///////////////////////////////////////////////////////////////////////////////
Cube_Face::Cube_Face()
{
    init(GREY);
}
///////////////////////////////////////////////////////////////////////////////
void Cube_Face::init(int iColor)
{
    for(int i=0;i<9;i++)
        _facet[i]=iColor;
}
///////////////////////////////////////////////////////////////////////////////
bool Cube_Face::is_solved() const
{
    int iCenter=_facet[0];

    for(int i=1;i<9;i++)
        if( (_facet[i]!=iCenter) && (_facet[i] != GREY) )
            return false;

    return true;
}
///////////////////////////////////////////////////////////////////////////////
bool Cube_Face::is_corner_solved() const
{
	int iCenter = _facet[0];

	for (int i = 2; i <=8; i+=2)
		if (_facet[i] != iCenter)
			return false;

	return true;
}
///////////////////////////////////////////////////////////////////////////////
bool Cube_Face::is_same_as(const Cube_Face& f) const
{
    for(int i=0;i<9;i++)
        if(_facet[i]!=f._facet[i])
            return false;

    return true;
}
///////////////////////////////////////////////////////////////////////////////
int& Cube_Face::facet(unsigned int i)
{
    assert(i<9);
    return _facet[i];
}
///////////////////////////////////////////////////////////////////////////////
int Cube_Face::facet(unsigned int i) const
{
    assert(i<9);
    return _facet[i];
}
///////////////////////////////////////////////////////////////////////////////
void Cube_Face::rotate_clockwise()
{
	//rotate edge
	int f1=_facet[1];
    _facet[1]=_facet[7];
    _facet[7]=_facet[5];
    _facet[5]=_facet[3];
    _facet[3]=f1;

	//rotate corners
	int f2=_facet[2];
    _facet[2]=_facet[8];
    _facet[8]=_facet[6];
    _facet[6]=_facet[4];
    _facet[4]=f2;
}
///////////////////////////////////////////////////////////////////////////////
void Cube_Face::rotate_counterclockwise()
{
    int f1=_facet[1];
    _facet[1]=_facet[3];
    _facet[3]=_facet[5];
    _facet[5]=_facet[7];
    _facet[7]=f1;

    int f2=_facet[2];
    _facet[2]=_facet[4];
    _facet[4]=_facet[6];
    _facet[6]=_facet[8];
    _facet[8]=f2;
}
///////////////////////////////////////////////////////////////////////////////
void Cube_Face::ignore_edge() // set all edge to grey
{
	_facet[1] = GREY;
	_facet[3] = GREY;
	_facet[5] = GREY;
	_facet[7] = GREY;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
Cube::Cube()
{
    init();
}
///////////////////////////////////////////////////////////////////////////////
Cube::~Cube()
{ }
///////////////////////////////////////////////////////////////////////////////
void Cube::init()
{
    _U.init(WHITE);
    _F.init(BLUE);
    _R.init(ORANGE);
    _L.init(RED);
    _D.init(YELLOW);
    _B.init(GREEN);
}

///////////////////////////////////////////////////////////////////////////////
void Cube::ignore_edge()
{
	_U.ignore_edge();
	_F.ignore_edge();
	_R.ignore_edge();
	_L.ignore_edge();
	_D.ignore_edge();
	_B.ignore_edge();
}
///////////////////////////////////////////////////////////////////////////////
bool Cube::is_solved() const
{
    if(!_U.is_solved())
        return false;

    if(!_R.is_solved())
        return false;

    if(!_L.is_solved())
        return false;

    if(!_F.is_solved())
        return false;

    if(!_D.is_solved())
        return false;

    return _B.is_solved();
}
///////////////////////////////////////////////////////////////////////////////
bool Cube::is_up_ring_solved() const
{
    int iF=_F.facet(0);
    if( (_F.facet(8)!=iF) || (_F.facet(1)!=iF) || (_F.facet(2)!=iF) )
        return false;

    int iR=_R.facet(0);
    if( (_R.facet(8)!=iR) || (_R.facet(7)!=iR) || (_R.facet(6)!=iR) )
        return false;

    int iL=_L.facet(0);
    if( (_L.facet(2)!=iL) || (_L.facet(3)!=iL) || (_L.facet(4)!=iL) )
        return false;

    int iB=_B.facet(0);
    if( (_B.facet(6)!=iB) || (_B.facet(5)!=iB) || (_B.facet(4)!=iB) )
        return false;

    return true;
}
///////////////////////////////////////////////////////////////////////////////
bool Cube::is_middle_ring_solved() const
{
    int iF=_F.facet(0);
    if( (_F.facet(7)!=iF) || (_F.facet(3)!=iF) )
        return false;

    int iR=_R.facet(0);
    if( (_R.facet(1)!=iR) || (_R.facet(5)!=iR) )
        return false;

    int iL=_L.facet(0);
    if( (_L.facet(1)!=iL) || (_L.facet(5)!=iL) )
        return false;

    int iB=_B.facet(0);
    if( (_B.facet(3)!=iB) || (_B.facet(7)!=iB) )
        return false;

    return true;
}
///////////////////////////////////////////////////////////////////////////////
bool Cube::is_down_ring_solved() const
{
    int iF=_F.facet(0);
    if( (_F.facet(6)!=iF) || (_F.facet(5)!=iF) || (_F.facet(4)!=iF) )
        return false;

    int iR=_R.facet(0);
    if( (_R.facet(2)!=iR) || (_R.facet(3)!=iR) || (_R.facet(4)!=iR) )
        return false;

    int iL=_L.facet(0);
    if( (_L.facet(8)!=iL) || (_L.facet(7)!=iL) || (_L.facet(6)!=iL) )
        return false;

    int iB=_B.facet(0);
    if( (_B.facet(8)!=iB) || (_B.facet(1)!=iB) || (_B.facet(2)!=iB) )
        return false;

    return true;
}
///////////////////////////////////////////////////////////////////////////////
bool Cube::is_oll_state() const
{
    return is_down_ring_solved() && is_middle_ring_solved() && _D.is_solved() ;
}
///////////////////////////////////////////////////////////////////////////////
bool Cube::is_pll_state() const
{
    return is_oll_state() && _U.is_solved();
}
///////////////////////////////////////////////////////////////////////////////
bool Cube::is_corners_solved() const //all corners solved, edge ignored
{
	if (!_U.is_corner_solved())
		return false;

	if (!_R.is_corner_solved())
		return false;

	if (!_L.is_corner_solved())
		return false;

	if (!_F.is_corner_solved())
		return false;

	if (!_D.is_corner_solved())
		return false;

	return _B.is_corner_solved();
}
///////////////////////////////////////////////////////////////////////////////
bool Cube::is_same_as(const Cube& c) const
{
    if(!_U.is_same_as(c._U))
        return false;

    if(!_R.is_same_as(c._R))
        return false;

    if(!_L.is_same_as(c._L))
        return false;

    if(!_F.is_same_as(c._F))
        return false;

    if(!_D.is_same_as(c._D))
        return false;

    if(!_B.is_same_as(c._B))
        return false;

    return true;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::U()
{
    _U.rotate_clockwise();

    int e7=_R.facet(7);
    _R.facet(7)=_B.facet(5);
    _B.facet(5)=_L.facet(3);
    _L.facet(3)=_F.facet(1);
    _F.facet(1)=e7;

    int e8=_R.facet(8);
    _R.facet(8)=_B.facet(6);
    _B.facet(6)=_L.facet(4);
    _L.facet(4)=_F.facet(2);
    _F.facet(2)=e8;

    int e4=_R.facet(6);
    _R.facet(6)=_B.facet(4);
    _B.facet(4)=_L.facet(2);
    _L.facet(2)=_F.facet(8);
    _F.facet(8)=e4;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::Ui()
{
    _U.rotate_counterclockwise();

    int e5=_B.facet(5);
    _B.facet(5)=_R.facet(7);
    _R.facet(7)=_F.facet(1);
    _F.facet(1)=_L.facet(3);
    _L.facet(3)=e5;

    int e4=_B.facet(4);
    _B.facet(4)=_R.facet(6);
    _R.facet(6)=_F.facet(8);
    _F.facet(8)=_L.facet(2);
    _L.facet(2)=e4;

    int e6=_B.facet(6);
    _B.facet(6)=_R.facet(8);
    _R.facet(8)=_F.facet(2);
    _F.facet(2)=_L.facet(4);
    _L.facet(4)=e6;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::U2()
{
    U(); U(); //todo optimize
}
///////////////////////////////////////////////////////////////////////////////
void Cube::R()
{
    _R.rotate_clockwise();

    int e3=_U.facet(3);
    _U.facet(3)=_F.facet(3);
    _F.facet(3)=_D.facet(3);
    _D.facet(3)=_B.facet(3);
    _B.facet(3)=e3;

    int e2=_U.facet(2);
    _U.facet(2)=_F.facet(2);
    _F.facet(2)=_D.facet(2);
    _D.facet(2)=_B.facet(2);
    _B.facet(2)=e2;

    int e4=_U.facet(4);
    _U.facet(4)=_F.facet(4);
    _F.facet(4)=_D.facet(4);
    _D.facet(4)=_B.facet(4);
    _B.facet(4)=e4;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::Ri()
{
    _R.rotate_counterclockwise();

    int e3=_U.facet(3);
    _U.facet(3)=_B.facet(3);
    _B.facet(3)=_D.facet(3);
    _D.facet(3)=_F.facet(3);
    _F.facet(3)=e3;

    int e2=_U.facet(2);
    _U.facet(2)=_B.facet(2);
    _B.facet(2)=_D.facet(2);
    _D.facet(2)=_F.facet(2);
    _F.facet(2)=e2;

    int e4=_U.facet(4);
    _U.facet(4)=_B.facet(4);
    _B.facet(4)=_D.facet(4);
    _D.facet(4)=_F.facet(4);
    _F.facet(4)=e4;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::R2()
{
    R(); R(); //todo optimize
}
///////////////////////////////////////////////////////////////////////////////
void Cube::r()
{
	R();
	Mi();
}
///////////////////////////////////////////////////////////////////////////////
void Cube::ri()
{
	Ri();
	M();
}
///////////////////////////////////////////////////////////////////////////////
void Cube::r2()
{
    R2();
    M2();
}
///////////////////////////////////////////////////////////////////////////////
void Cube::L()
{
    _L.rotate_clockwise();

    int e7=_U.facet(7);
    _U.facet(7)=_B.facet(7);
    _B.facet(7)=_D.facet(7);
    _D.facet(7)=_F.facet(7);
    _F.facet(7)=e7;

    int e8=_U.facet(8);
    _U.facet(8)=_B.facet(8);
    _B.facet(8)=_D.facet(8);
    _D.facet(8)=_F.facet(8);
    _F.facet(8)=e8;

    int e6=_U.facet(6);
    _U.facet(6)=_B.facet(6);
    _B.facet(6)=_D.facet(6);
    _D.facet(6)=_F.facet(6);
    _F.facet(6)=e6;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::Li()
{
    _L.rotate_counterclockwise();

    int e7=_U.facet(7);
    _U.facet(7)=_F.facet(7);
    _F.facet(7)=_D.facet(7);
    _D.facet(7)=_B.facet(7);
    _B.facet(7)=e7;

    int e8=_U.facet(8);
    _U.facet(8)=_F.facet(8);
    _F.facet(8)=_D.facet(8);
    _D.facet(8)=_B.facet(8);
    _B.facet(8)=e8;

    int e6=_U.facet(6);
    _U.facet(6)=_F.facet(6);
    _F.facet(6)=_D.facet(6);
    _D.facet(6)=_B.facet(6);
    _B.facet(6)=e6;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::L2()
{
    L(); L(); //todo optimize
}
///////////////////////////////////////////////////////////////////////////////
void Cube::l()
{
    L();
    M();
}
///////////////////////////////////////////////////////////////////////////////
void Cube::li()
{
    Li();
    Mi();
}
///////////////////////////////////////////////////////////////////////////////
void Cube::l2()
{
    L2();
    M2();
}
///////////////////////////////////////////////////////////////////////////////
void Cube::F()
{
    _F.rotate_clockwise();

    int e5=_U.facet(5);
    _U.facet(5)=_L.facet(5);
    _L.facet(5)=_D.facet(1);
    _D.facet(1)=_R.facet(5);
    _R.facet(5)=e5;

    int e6=_U.facet(6);
    _U.facet(6)=_L.facet(6);
    _L.facet(6)=_D.facet(2);
    _D.facet(2)=_R.facet(6);
    _R.facet(6)=e6;

    int e4=_U.facet(4);
    _U.facet(4)=_L.facet(4);
    _L.facet(4)=_D.facet(8);
    _D.facet(8)=_R.facet(4);
    _R.facet(4)=e4;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::Fi()
{
    _F.rotate_counterclockwise();

    int e5=_U.facet(5);
    _U.facet(5)=_R.facet(5);
    _R.facet(5)=_D.facet(1);
    _D.facet(1)=_L.facet(5);
    _L.facet(5)=e5;

    int e6=_U.facet(6);
    _U.facet(6)=_R.facet(6);
    _R.facet(6)=_D.facet(2);
    _D.facet(2)=_L.facet(6);
    _L.facet(6)=e6;

    int e4=_U.facet(4);
    _U.facet(4)=_R.facet(4);
    _R.facet(4)=_D.facet(8);
    _D.facet(8)=_L.facet(4);
    _L.facet(4)=e4;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::F2()
{
    F(); F(); //todo optimize
}
///////////////////////////////////////////////////////////////////////////////
void Cube::D()
{
    _D.rotate_clockwise();

    int e5=_F.facet(5);
    _F.facet(5)=_L.facet(7);
    _L.facet(7)=_B.facet(1);
    _B.facet(1)=_R.facet(3);
    _R.facet(3)=e5;

    int e6=_F.facet(6);
    _F.facet(6)=_L.facet(8);
    _L.facet(8)=_B.facet(2);
    _B.facet(2)=_R.facet(4);
    _R.facet(4)=e6;

    int e4=_F.facet(4);
    _F.facet(4)=_L.facet(6);
    _L.facet(6)=_B.facet(8);
    _B.facet(8)=_R.facet(2);
    _R.facet(2)=e4;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::Di()
{
    _D.rotate_counterclockwise();

    int e5=_F.facet(5);
    _F.facet(5)=_R.facet(3);
    _R.facet(3)=_B.facet(1);
    _B.facet(1)=_L.facet(7);
    _L.facet(7)=e5;

    int e6=_F.facet(6);
    _F.facet(6)=_R.facet(4);
    _R.facet(4)=_B.facet(2);
    _B.facet(2)=_L.facet(8);
    _L.facet(8)=e6;

    int e4=_F.facet(4);
    _F.facet(4)=_R.facet(2);
    _R.facet(2)=_B.facet(8);
    _B.facet(8)=_L.facet(6);
    _L.facet(6)=e4;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::D2()
{
    D(); D(); //todo optimize
}
///////////////////////////////////////////////////////////////////////////////
void Cube::B()
{
    _B.rotate_clockwise();

    int e1=_U.facet(1);
    _U.facet(1)=_R.facet(1);
    _R.facet(1)=_D.facet(5);
    _D.facet(5)=_L.facet(1);
    _L.facet(1)=e1;

    int e2=_U.facet(2);
    _U.facet(2)=_R.facet(2);
    _R.facet(2)=_D.facet(6);
    _D.facet(6)=_L.facet(2);
    _L.facet(2)=e2;

    int e8=_U.facet(8);
    _U.facet(8)=_R.facet(8);
    _R.facet(8)=_D.facet(4);
    _D.facet(4)=_L.facet(8);
    _L.facet(8)=e8;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::Bi()
{
    _B.rotate_counterclockwise();

    int e1=_U.facet(1);
    _U.facet(1)=_L.facet(1);
    _L.facet(1)=_D.facet(5);
    _D.facet(5)=_R.facet(1);
    _R.facet(1)=e1;

    int e2=_U.facet(2);
    _U.facet(2)=_L.facet(2);
    _L.facet(2)=_D.facet(6);
    _D.facet(6)=_R.facet(2);
    _R.facet(2)=e2;

    int e8=_U.facet(8);
    _U.facet(8)=_L.facet(8);
    _L.facet(8)=_D.facet(4);
    _D.facet(4)=_R.facet(8);
    _R.facet(8)=e8;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::B2()
{
    B(); B(); //todo optimize
}
///////////////////////////////////////////////////////////////////////////////
void Cube::M()
{
    int e1=_U.facet(1);
    _U.facet(1)=_B.facet(1);
    _B.facet(1)=_D.facet(1);
    _D.facet(1)=_F.facet(1);
    _F.facet(1)=e1;

    int e0=_U.facet(0);
    _U.facet(0)=_B.facet(0);
    _B.facet(0)=_D.facet(0);
    _D.facet(0)=_F.facet(0);
    _F.facet(0)=e0;

    int e5=_U.facet(5);
    _U.facet(5)=_B.facet(5);
    _B.facet(5)=_D.facet(5);
    _D.facet(5)=_F.facet(5);
    _F.facet(5)=e5;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::Mi()
{
    int e1=_U.facet(1);
    _U.facet(1)=_F.facet(1);
    _F.facet(1)=_D.facet(1);
    _D.facet(1)=_B.facet(1);
    _B.facet(1)=e1;

    int e0=_U.facet(0);
    _U.facet(0)=_F.facet(0);
    _F.facet(0)=_D.facet(0);
    _D.facet(0)=_B.facet(0);
    _B.facet(0)=e0;

    int e5=_U.facet(5);
    _U.facet(5)=_F.facet(5);
    _F.facet(5)=_D.facet(5);
    _D.facet(5)=_B.facet(5);
    _B.facet(5)=e5;
}
///////////////////////////////////////////////////////////////////////////////
void Cube::M2()
{
    M(); M(); //todo optimize
}
///////////////////////////////////////////////////////////////////////////////
Cube_Face& Cube::faceR()
{ return _R; }
///////////////////////////////////////////////////////////////////////////////
Cube_Face& Cube::faceL()
{ return _L; }
///////////////////////////////////////////////////////////////////////////////
Cube_Face& Cube::faceU()
{ return _U; }
///////////////////////////////////////////////////////////////////////////////
Cube_Face& Cube::faceF()
{ return _F; }
///////////////////////////////////////////////////////////////////////////////
Cube_Face& Cube::faceD()
{ return _D; }
///////////////////////////////////////////////////////////////////////////////
Cube_Face& Cube::faceB()
{ return _B; }
///////////////////////////////////////////////////////////////////////////////
void Cube::rotate(const vector<int>& vsSeq)
{
    // todo optimise
	for (unsigned int i = 0; i < vsSeq.size(); i++)
	{
		int sRot = vsSeq[i];
		
		if (sRot == ROT_U) U();
		else if (sRot == ROT_Up) Ui();
		else if (sRot == ROT_U2) U2();
	
		else if (sRot == ROT_R) R();
		else if (sRot == ROT_Rp) Ri();
		else if (sRot == ROT_R2) R2();
	/*
		else if (sRot == "r") r();
		else if (sRot == "r'") ri();
		else if (sRot == "r2") r2();
    */
		else if (sRot == ROT_L) L();
		else if (sRot == ROT_Lp) Li();
		else if (sRot == ROT_L2) L2();
	/*
        else if (sRot == "l") l();
        else if (sRot == "l'") li();
        else if (sRot == "l2") l2();
    */    
        else if (sRot == ROT_F) F();
		else if (sRot == ROT_Fp) Fi();
		else if (sRot == ROT_F2) F2();

		else if (sRot == ROT_D) D();
		else if (sRot == ROT_Dp) Di();
		else if (sRot == ROT_D2) D2();

		else if (sRot == ROT_B) B();
		else if (sRot == ROT_Bp) Bi();
		else if (sRot == ROT_B2) B2();

		else if (sRot == ROT_M) M();
		else if (sRot == ROT_Mp) Mi();
		else if (sRot == ROT_M2) M2();
	}
}
///////////////////////////////////////////////////////////////////////////////
void Cube::rotate(const string& sSeq)
{
    Sequence s;
    s.set(sSeq);
    rotate(s.rotations());
}
///////////////////////////////////////////////////////////////////////////////
