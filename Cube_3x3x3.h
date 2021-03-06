#ifndef Cube_3x3x3_
#define Cube_3x3x3_

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

class Cube_3x3x3_Face
{
public:
    Cube_3x3x3_Face();
    void init(int iColor);

    bool is_solved() const;
	bool is_corner_solved() const;
    bool is_same_as(const Cube_3x3x3_Face& f) const;

	void ignore_edge(); // set all edge to grey

    int& facet(unsigned int i); //center is [0]
    int facet(unsigned int i) const; //center is [0]

    void rotate_clockwise();
    void rotate_counterclockwise();

private:
    int _facet[9];
};

class Cube_3x3x3
{
public:
    Cube_3x3x3();
    ~Cube_3x3x3();
    void init(); // Up is white, Front is blue

	void ignore_edge(); // write all edge to grey

    //cube tests
    bool is_solved() const;
    bool is_up_ring_solved() const;
    bool is_middle_ring_solved() const;
    bool is_down_ring_solved() const;
    bool is_ready_for_oll() const; //all solved but not upper layer
    bool is_ready_for_pll() const; //all solved but not upper ring
	bool is_corners_solved() const; //all corners solved, edge ignored
	bool is_same_as(const Cube_3x3x3& c) const;

    //rotations
    void rotate(string sSeq); //sSeq can be "R U'L2 " ...
	void rotate(vector<string>& vsSeq);

	//split sequence, utility function
	static void split(string sSeq, vector<string>& vsSeq);
	static void unsplit(const vector<string>& vsSeq, string& sSeq );

    // faces access
    Cube_3x3x3_Face& faceR();
    Cube_3x3x3_Face& faceL();
    Cube_3x3x3_Face& faceU();
    Cube_3x3x3_Face& faceF();
    Cube_3x3x3_Face& faceD();
    Cube_3x3x3_Face& faceB();

private:
	void U();
	void Ui();
	void U2();

	void R();
	void Ri();
	void R2();

	void L();
	void Li();
	void L2();

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

    Cube_3x3x3_Face _R,_L,_U,_F,_D,_B;
};

#endif
