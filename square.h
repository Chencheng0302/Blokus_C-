#pragma once
#include <string>
#include"block.h"
class square
{
public:
	square(int givenX, int givenY);
	int getX();
	int getY();
	int getOwner();
	void setOwner(int givenOwner);
	void setOccupyer(int occupiedTileID);
	void setTile(block *target);
	int getOccupier();
private:
	int x, y, owner, occupier;
};

