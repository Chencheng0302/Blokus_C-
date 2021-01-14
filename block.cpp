#include "block.h"
#include<cstring>
#include <iostream>
using namespace std;

block::block(int idNum, int givenOwner)
{
	id = idNum;
	owner = givenOwner;
	x = 0;
	y = 0;
	numOfSquares = 0;
	isPlaced = false;
	switch (id)
	{
	case 1://single sqaure
		numOfSquares = 1;
		x = 1;
		y = 1;
		symmetry = true;
		shape[0][0] = 1;
		break;
	case 2://2 units line
		numOfSquares = 2;
		x = 2;
		y = 1;
		symmetry = true;
		memset(shape[0],1,2);
		break;
	case 3://3 units line
		numOfSquares = 3;
		x = 3;
		y = 1;
		symmetry = true;
		memset(shape[0], 1, 3);
		break;
	case 4://right angle
		numOfSquares = 3;
		x = 2;
		y = 2;
		symmetry = true;
		shape[0][0] = 1;
		memset(shape[1], 1, 2);
		break;
	case 5://4 units line
		numOfSquares = 4;
		x = 4;
		y = 1;
		symmetry = true;
		memset(shape[0], 1, 4);
		break;
	case 6://2 unit square
		numOfSquares = 4;
		x = 2;
		y = 2;
		symmetry = true;
		memset(shape[0],1,2);
		memset(shape[1], 1, 2);
		break;
	case 7://long right angle
		numOfSquares = 4;
		x = 3;
		y = 2;
		symmetry = false;
		shape[0][0] =  1 ;
		memset(shape[1], 1, 3*sizeof(bool));
		break;
	case 8://fort
		numOfSquares = 4;
		x = 3;
		y = 2;
		symmetry = true;
		memset(shape[1], 1, 3);
		shape[0][1] = 1;
		break;
	case 9:	//step	**
			//		 **
		numOfSquares = 4;
		x = 3;
		y = 2;
		symmetry = false;
		memset(shape[0], 1, 2);
		shape[1][1] = 1;
		shape[1][2] = 1;
		break;
	case 10://5 units line
		numOfSquares = 5;
		x = 5;
		y = 1;
		symmetry = true;
		memset(shape[0], 1, 5);
		break;
	case 11://plus
		numOfSquares = 5;
		x = 3;
		y = 3;
		symmetry = true;
		memset(shape[1], 1, 3);
		shape[0][1] = 1;
		shape[2][1] = 1;
		break;
	case 12://long right angle	*
			//					****
		numOfSquares = 5;
		x = 4;
		y = 2;
		symmetry = false;
		shape[0][0] = 1;
		memset(shape[1], 1, 4);
		break;
	case 13://big right angle	*
			//					*
			//					***
		numOfSquares = 5;
		x = 3;
		y = 3;
		symmetry = false;
		memset(shape[2], 1, 3);
		shape[0][0] = 1;
		shape[1][0] = 1;
		break;
	case 14://long fort	 *
			//			****
		numOfSquares = 5;
		x = 4;
		y = 2;
		symmetry = false;
		memset(shape[1], 1, 4);
		shape[0][1] = 1;
		break;
	case 15://fortress	* *
			//			***
		numOfSquares = 5;
		x = 3;
		y = 2;
		symmetry = false;
		shape[0][0] = 1;
		shape[0][2] = 1;
		memset(shape[1], 1, 3);
		break;
	case 16://lie down six	**
			//				***
		numOfSquares = 5;
		x = 3;
		y = 2;
		symmetry = false;
		memset(shape[0], 1, 2);
		memset(shape[1], 1, 3);
		break;
	case 17://long step		**
			//				 ***
		numOfSquares = 5;
		x = 4;
		y = 2;
		symmetry = false;
		memset(shape[0], 1, 2);
		shape[1][1] = 1;
		shape[1][2] = 1;
		shape[1][3] = 1;
		break;
	case 18://high fort		*
			//				*
			//			   ***
		numOfSquares = 5;
		x = 3;
		y = 3;
		symmetry = true;
		memset(shape[2], 1, 3);
		shape[0][1] = 1;
		shape[1][1] = 1;
		break;
	case 19://high step		**
			//				 *
			//				 **
		numOfSquares = 5;
		x = 3;
		y = 3;
		symmetry = false;
		memset(shape[0], 1, 2);
		shape[1][1] = 1;
		shape[2][1] = 1;
		shape[2][2] = 1;
		break;
	case 20://big step		*
			//				**
			//				 **
		numOfSquares = 5;
		x = 3;
		y = 3;
		symmetry = false;
		memset(shape[1], 1, 2);
		shape[0][0] = 1;
		shape[2][1] = 1;
		shape[2][2] = 1;
		break;
	case 21://broken plus		*
			//					***
			//					 *
		numOfSquares = 5;
		x = 3;
		y = 3;
		symmetry = false;
		memset(shape[1], 1, 3);
		shape[0][0] = 1;
		shape[2][1] = 1;
		break;
	default:
		cout << "Parameters Error." << endl;
		break;
	}
}


void block::putOn(int location)
{
	//int count_of_matched_square = 0;
	////int area = x * y;
	//for (size_t i = 0; i < 5; i++)
	//{
	//	for (size_t j = 0; j < 5; j++) {
	//		if (shape[i][j] == 1) {
	//			count_of_matched_square++;
	//			temp.push_back(owner);
	//		}
	//		else temp.push_back(shape[i][j]);
	//	}
	//	if (count_of_matched_square == numOfSquares) break;
	//}
}

int block::getOwner()
{
	return owner;
}

vector<int> block::getBlock()
{
	vector<int> temp;
	for (size_t i = 0; i < y; i++)
	{	
		for (size_t j = 0; j < x; j++) {
			if (shape[i][j] == 1) temp.push_back(owner);
			else temp.push_back(0);
		}
	}
	return temp;
}

int block::getX()
{
	return x;
}

int block::getY()
{
	return y;
}

int block::getNum()
{
	return numOfSquares;
}

int block::getID()
{
	return id;
}

void block::rotate(bool rotateToLeft)
{
	//if(id==11||id==6)
	int n = 5, temp = 0,lefttop_index_x,lefttop_index_y;
	bool encountered_sqaure = false;
	if (rotateToLeft) {
		lefttop_index_x = n-x;
		lefttop_index_y = 0;
		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < n - i - 1; j++) {
				if (i == 1 && j == 0) continue;
				int temp = shape[i][j];
				shape[i][j] = shape[j][n - 1 - i];
				shape[j][n - 1 - i] = shape[n - 1 - i][n - 1 - j];
				shape[n - 1 - i][n - 1 - j] = shape[n - 1 - j][i];
				shape[n - 1 - j][i] = temp;
			}
		}
	}
	else
	{
		lefttop_index_x = 0;
		lefttop_index_y = n - y;
		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < n - i - 1; j++) {
				if (i == 1 && j == 0) continue;
				int temp = shape[i][j];
				shape[i][j] = shape[n - 1 - j][i];
				shape[n - 1 - j][i] = shape[n - 1 - i][n - 1 - j];
				shape[n - 1 - i][n - 1 - j] = shape[j][n - 1 - i];
				shape[j][n - 1 - i] = temp;
			}
		}
	}
	temp = x;
	x = y;
	y = temp;
	replace(lefttop_index_x, lefttop_index_y);
}

void block::reverse()
{
	int n = 5;
	for (int i = 0; i < 5; i++) {
		for (size_t j = 0; j < (n - 1) / 2; j++)
		{
			int temp = shape[i][j];
			shape[i][j] = shape[i][n - 1 - j];
			shape[i][n - 1 - j] = temp;
		}
	}
	replace(0, n-x);
}

void block::replace(int lefttop_x, int lefttop_y)
{
	for (size_t i = 0; i < y; i++)
	{
		for (size_t j = 0; j < x; j++) {
			shape[i][j] = shape[lefttop_x + i][lefttop_y + j];
			shape[lefttop_x + i][lefttop_y + j] = false;
		}
	}
}

//void block::placedAt(square* loc)
//{
//	squareLocationRecords.push_back(loc);
//}
//
//vector<square*> block::getSquaresLoc()
//{
//	return squareLocationRecords;
//}
//

bool block::hasBeenPlaced()
{
	return isPlaced;
}

bool block::getSymmetry()
{
	return symmetry;
}

void block::displayBlock()
{
	cout << id <<':'<< endl;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (shape[i][j] == 0) cout << ' ';
			else cout << '@'; 
		}
		cout << endl;
	}
}
