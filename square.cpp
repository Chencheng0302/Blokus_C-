#include "square.h"
square::square(int givenX, int givenY)
{
	 x = givenX;
	 y = givenY;
	 owner = 0;
	 occupier = 0;
}

int square::getX()
{
	return x;
}

int square::getY()
{
	return y;
}

int square::getOwner()
{
	return owner;
}

void square::setOwner(int givenOwner)
{
	owner = givenOwner;
}

void square::setOccupyer(int occupiedTileID)
{
	occupier = occupiedTileID;
}

void square::setTile(block* target)
{
	owner = target->getOwner();
	occupier = target->getID();
}

int square::getOccupier()
{
	return occupier;
}

