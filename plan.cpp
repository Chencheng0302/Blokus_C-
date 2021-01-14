#include "plan.h"

plan::plan(int plan_x, int plan_y, block* givenTile)
{
	x = plan_x;
	y = plan_y;
	payoff = 0;
	numOfSamePlan = 0;
	tile = givenTile;
}

plan::plan(int plan_x, int plan_y,int exp_payoff, block* givenTile)
{
	x = plan_x;
	y = plan_y;
	payoff = exp_payoff;
	numOfSamePlan = 0;
	tile = givenTile;
}

int plan::getX()
{
	return x;
}

int plan::getY()
{
	return y;
}

int plan::getPayoff()
{
	return payoff;
}

int plan::getNumOfSamePlan()
{
	return numOfSamePlan;
}


void plan::foundSamePlan()
{
	numOfSamePlan++;
}

block* plan::getTile()
{
	return tile;
}

bool plan::equaulsTo(plan* thePlan)
{
	if (x == thePlan->getX() && y == thePlan->getY())
		return true;
	return false;
}

