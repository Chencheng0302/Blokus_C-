#pragma once
#include"block.h"
#include"plan.h"
#include"square.h"
#include <vector>
#include <string>
using namespace std;
struct dataset {
	int origin_x;
	int origin_y;
	int kx;
	int ky;
};
class player
{
public:
	player(int id, string name);
	void displayRemainingBlocks();
	void setBlock(int pos);
	block* getBlock(int id);
	block* getSpecificBlock(block* target);
	int getID();
	
	void putBlock(int pos);
	void putSpecificBlock(block* target);
	vector<block*> getRemainingBlocks();
	void setAvailableSquare(square* target);
	void cleanSquaresRecord();
	void perfectlyPlaced();
	vector<square*> getAvailableSquares();
	vector<square*> getAvailableSquares(int topleftX, int topleftY, int width, int height);
	vector<plan*> getPlans();
	string getName();
	void passed();
	bool hasBeenPassed();
	bool isPefectlyPlaced();
	void addPlan(plan* givenPlan);
	void clearPlans();
	dataset getParameters();
private:
	int indexTranslate(int original_index);
	vector<block*> ownBlocks;
	vector<square*>availableSquares;
	vector<plan*>placementPlans;
	string playerName;
	bool isPassed;
	bool isPerfectlyPlaced;
	bool tileStatus[21];
	int playerID;
	dataset parameters;
};

