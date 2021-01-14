#pragma once
#include"block.h"
class plan
{
public:
	plan(int plan_x, int plan_y, block* givenTile);
	plan(int plan_x,int plan_y,int exp_payoff, block* givenTile);
	int getX();
	int getY();
	int getPayoff();
	int getNumOfSamePlan();
	void foundSamePlan();
	block* getTile();
	//bool operator==(const plan& givenPlan);
	bool equaulsTo(plan* thePlan);
private:
	int x, y, payoff, numOfSamePlan;
	block* tile;
};

