#include "player.h"
#include "block.h"
#include <iostream>
#include<vector>
using namespace std;
player::player(int id, string name)
{
	playerID = id;
	playerName = name;
	block* singleBlock;
	isPassed = false;
	isPerfectlyPlaced = false;
	for (int i = 1; i <= 21; i++)
	{
		singleBlock = new block(i, playerID);
		ownBlocks.push_back(singleBlock);
		tileStatus[i - 1] = true;
	}
	switch (playerID)
	{
	case 1:
		parameters.origin_x = 0;
		parameters.origin_y = 0;
		parameters.kx = 1;
		parameters.ky = 1;
		break;
	case 2:
		parameters.origin_x = 0;
		parameters.origin_y = 19;
		parameters.kx = 1;
		parameters.ky = -1;
		break;
	case 3:
		parameters.origin_x = 19;
		parameters.origin_y = 0;
		parameters.kx = -1;
		parameters.ky = 1;
		break;
	case 4:
		parameters.origin_x = 19;
		parameters.origin_y = 19;
		parameters.kx = -1;
		parameters.ky = -1;
		break;
	default:
		break;
	}
	singleBlock = nullptr;
}

void player::displayRemainingBlocks()
{
	cout << "Player " << playerID << "'s Remaining tiles are listed as following:" << endl;
	for (auto it : ownBlocks) it->displayBlock();
}

void player::setBlock(int pos)
{
	tileStatus[pos] = false;
}

block* player::getBlock(int id)
{
	return ownBlocks.at(id);

}

block* player::getSpecificBlock(block* target)
{
	int id = target->getID(), index = 0;
	for (int i = 0; i < ownBlocks.size(); i++) {
		if (ownBlocks.at(i)->getID() == id) {
			index = i;
		}
	}
	//int index = indexTranslate(id);
	return ownBlocks.at(index);
}



int player::getID()
{
	return playerID;
}

int player::indexTranslate(int original_index)
{
	int index = original_index;
	for (int i = 0; i < 21; i++) {
		if (i <= original_index) {
			if (!tileStatus[i]) {
				index--;
			}
		}

	}
	return index;
}

void player::putBlock(int pos)
{
	tileStatus[pos] = false;
	ownBlocks.erase(ownBlocks.begin()+pos);
}

void player::putSpecificBlock(block* target)
{
	int id = target->getID(),index=0;
	for (int i = 0; i < ownBlocks.size(); i++) {
		if (ownBlocks.at(i)->getID() == id) {
			index = i;
		}
	}
	tileStatus[index] = false;
	ownBlocks.erase(ownBlocks.begin() + index);
}

vector<block*> player::getRemainingBlocks()
{
	return ownBlocks;
}

void player::setAvailableSquare(square* target)
{
	availableSquares.push_back(target);
	if (availableSquares.size() > 1) {
		for (int i = 0; i < availableSquares.size(); i++) {
			switch (playerID)
			{
			case 1:
				if (availableSquares[i]->getX() > availableSquares.back()->getX() && availableSquares[i]->getY() > availableSquares.back()->getY()) {
					availableSquares.push_back(availableSquares[i]);
					availableSquares.erase(availableSquares.begin()+i);
				}
				break;
			case 2:
				if (availableSquares[i]->getX() < availableSquares.back()->getX() && availableSquares[i]->getY() > availableSquares.back()->getY()) {
					availableSquares.push_back(availableSquares[i]);
					availableSquares.erase(availableSquares.begin() + i);
				}
				break;
			case 3:
				if (availableSquares[i]->getX() > availableSquares.back()->getX() && availableSquares[i]->getY() < availableSquares.back()->getY()) {
					availableSquares.push_back(availableSquares[i]);
					availableSquares.erase(availableSquares.begin() + i);
				}
				break;
			case 4:
				if (availableSquares[i]->getX() < availableSquares.back()->getX() && availableSquares[i]->getY() < availableSquares.back()->getY()) {
					availableSquares.push_back(availableSquares[i]);
					availableSquares.erase(availableSquares.begin() + i);
				}
				break;
			default:
				break;
			}
		}
	}
}

void player::cleanSquaresRecord()
{
	availableSquares.clear();
}

void player::perfectlyPlaced()
{
	isPerfectlyPlaced = true;
}

vector<square*> player::getAvailableSquares()
{
	return availableSquares;
}

vector<square*> player::getAvailableSquares(int topleftX, int topleftY, int width, int height)
{
	vector<square*> squares;
	for (auto it : availableSquares) {
		if ((it->getX() >= topleftX && it->getX() <= topleftX + height) && (it->getY() >= topleftY && it->getY() <= topleftY + width))
			squares.push_back(it);
	}
	return squares;
}

vector<plan*> player::getPlans()
{
	return placementPlans;
}

string player::getName()
{
	return playerName;
}

void player::passed()
{
	isPassed = true;
}

bool player::hasBeenPassed()
{
	return isPassed;
}

bool player::isPefectlyPlaced()
{
	return isPerfectlyPlaced;
}

void player::addPlan(plan* givenPlan)
{
	placementPlans.push_back(givenPlan);
}

void player::clearPlans()
{
	placementPlans.clear();
}

dataset player::getParameters()
{
	return parameters;
}
