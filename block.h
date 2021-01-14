#pragma once
#include <vector>
using namespace std;
class block
{
public:
	block(int idnum, int givenOwner);
	void putOn(int location);
	void displayBlock();
	int getOwner();
	vector<int> getBlock();
	int getX();
	int getY();
	int getNum();
	int getID();
	void rotate(bool rotateToLeft);
	void reverse();
	void replace(int lefttop_x,int lefttop_y);
	/*void placedAt(square* loc);
	vector<square*> getSquaresLoc();*/
	bool hasBeenPlaced();
	bool getSymmetry();
private:
	int id, numOfSquares, x, y, owner;
	bool symmetry, isPlaced;
	bool shape[5][5] = { {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0} };
	//vector<square*> squareLocationRecords;
};

