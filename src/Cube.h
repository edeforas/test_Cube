#ifndef _Cube_
#define _Cube_

#include <string>
#include <vector>
using namespace std;

#define GREY (0) //invalid or ignored color
#define WHITE (1)
#define YELLOW (2)
#define RED (3)
#define ORANGE (4)
#define BLUE (5)
#define GREEN (6)


//cube facet index is:

// 8 1 2
// 7 0 3
// 6 5 4

class Cube_Face
{
public:
    Cube_Face();
    void init(int iColor);

    bool is_solved() const;
	bool is_corner_solved() const;
    bool is_same_as(const Cube_Face& f) const;

	void ignore_edges(); // set all edge to grey

    int& facet(unsigned int i); //center is [0]
    int facet(unsigned int i) const; //center is [0]

    void rotate_clockwise();
    void rotate_counterclockwise();

private:
    int _facet[9];
};

class Cube
{
public:
    Cube();
    ~Cube();
    void init(); // Up is white, Front is blue

	void ignore_edges(); // write all edge to grey

    //cube tests
    bool is_solved() const;
    bool is_up_ring_solved() const;
    bool is_middle_ring_solved() const;
    bool is_down_ring_solved() const;
    bool is_oll_state() const; //all solved but not upper layer
    bool is_pll_state() const; //all solved but not upper ring
	bool is_corners_solved() const; //all corners solved, edge ignored
	bool is_same_as(const Cube& c) const;

    //rotations
    void rotate(const string& sSeq); //sSeq can be "R U' L2 " ... use spaces for now
	void rotate(const vector<int>& vsSeq); //use optimized seq definition

    // faces access
    Cube_Face& faceR();
    Cube_Face& faceL();
    Cube_Face& faceU();
    Cube_Face& faceF();
    Cube_Face& faceD();
    Cube_Face& faceB();

private:
	void U();
	void Ui();
	void U2();

	void R();
	void Ri();
	void R2();

	void r();
	void ri();
	void r2();
	   
	void L();
	void Li();
	void L2();

	void l();
	void li();
	void l2();

	void F();
	void Fi();
	void F2();

	void D();
	void Di();
	void D2();

	void B();
	void Bi();
	void B2();

	void M();
	void Mi();
	void M2();

    Cube_Face _R,_L,_U,_F,_D,_B;
};

#endif
