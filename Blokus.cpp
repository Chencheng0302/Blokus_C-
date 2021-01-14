#include <iostream>
#include <cstring>
#include <vector>
#include<Windows.h>
#include<cmath>
#include <time.h>
#include<deque>

#include"plan.h"
#include"block.h"
#include"square.h"
#include"player.h"

using namespace std;

struct axis {
	int x;
	int y;
};


void displayBoard(int x, int y, int width, int height);
//void putBlock(int paraX, int paraY, block* par);
bool isPlaceable(block* tile, int posX, int posY);
void RecordAvailbleSquares(int x,int y, int width, int height, int skipedPlayer);
bool humanPlacement(int parax, int paray, block* target);

void AI(player* aiPlayer);

vector<player*> playerSet;
square* board[20][20]={nullptr};
//block* singleBlock;


int turn = 1;


int main()
{
	srand(time(0));
	bool gameover = false;
	square* unitSquare = nullptr;
	int useless = 0;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			unitSquare = new square(i, j);
			board[i][j] = unitSquare;
		}

	player* ai;
	for (size_t i = 1; i <= 4; i++)
	{
		ai = new player(i, "ai");
		playerSet.push_back(ai);
	}
	ai = nullptr;
	int x, y, id;
	displayBoard(0, 0, 20, 20);
	while (!gameover)
	{
		for (size_t i = 0; i < 4; i++)
		{
			//if (i == 0) {
			//	bool placed = false;
			//	while (!placed) {
			//		cin >> x >> y >> id;
			//		placed = humanPlacement(x, y, playerSet.at(i)->getRemainingBlocks().at(id - 1));
			//	}
			//}
			//else {
				ai = playerSet.at(i);
				if (ai->hasBeenPassed())continue;
				AI(ai);
				RecordAvailbleSquares(0, 0, 20, 20,0);
				//ai->displayRemainingBlocks();
				//vector<square*> avail = ai->getAvailableSquares();
				//for (auto it : avail) {
				//	cout << "P" << ai->getID() << ": x: " << it->getX() << " y: " << it->getY() << endl;
				//}
			//}
		}
		gameover = true;
		for (auto it : playerSet) {
			if (!it->hasBeenPassed())gameover = false;
		}
		displayBoard(0, 0, 20, 20);
		
		cin >> useless;
		turn++;
	}
	cout << "Game Over" << endl;
	cout << "\tScoreboard" << endl;
	for (auto it : playerSet) {
		int score = 0;
		vector<block*> remainingBlocks=it->getRemainingBlocks();
		if (remainingBlocks.empty()) {
			score += 15;
			if (it->isPefectlyPlaced()) score += 5;
		}
		for (auto itr : remainingBlocks) {
			score -= itr->getNum();
		}
		cout << it->getName() << ": " << '\t' << score << endl;
	}
	system("pause");
}
void displayBoard(int x,int y, int width, int height) {
		for (int i = x; i < height; i++)
		{
			for (int j = y; j < width; j++)
			{
				if (i < 0 || i>19 || j < 0 || j>19)continue;
					switch (board[i][j]->getOwner())
					{
					case 1:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
						break;
					case 2:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
						break;
					case 3:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
						break;
					case 4:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
						break;
					default:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
						break;
					}
					cout << board[i][j]->getOwner() << " ";
					//GRAY  //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
					//WHITE //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			}
			cout << endl;
		}

	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void putBlock(int paraX, int paraY, block* par, bool undo) {
	vector<int> tempTransfer = par->getBlock();
	int count = 0, total = par->getNum(), x = paraX, y = paraY, id = par->getID();
	for (size_t i = 0; i < par->getY(); i++)
	{
		for (size_t j = 0; j < par->getX(); j++)
		{
			
			if (count == total)break;
			else if (tempTransfer.front() != 0)
			{
				if (undo) {
					board[x][y]->setOwner(0);
					board[x][y]->setOccupyer(0);
				} 
				else board[x][y]->setTile(par);
				count++;
			}
			tempTransfer.erase(tempTransfer.begin());
			y++;
		}
		y = paraY;
		x++;
	}
}
bool isPlaceable(block* tile, int posX, int posY) {
	int count = 0, x = posX, y = posY, width = tile->getX(), height = tile->getY(), total = tile->getNum(), owner = tile->getOwner();
	bool isPlaceable = false;
	vector<int> tempTransfer = tile->getBlock();
	if (x + height-1 > 19 || y + width-1 > 19 || x < 0 || y < 0) return false;
	else if (turn == 1) {
		if ((x == 0 && y == 0 && tempTransfer.front() == 0) || (x == 0 && y + width - 1 == 19 && tempTransfer.at(width - 1) == 0) || (x + height - 1 == 19 && y == 0 && tempTransfer.at(width * height - width) == 0) || (x + height - 1 == 19 && y + width - 1 == 19 && tempTransfer.size() != width * height)) return false;
		else if ((x == 0 && y == 0 && tempTransfer.front() != 0) || (x == 0 && y + width - 1 == 19 && tempTransfer.at(width - 1) != 0) || (x + height - 1 == 19 && y == 0 && tempTransfer.at(width * height - width) != 0) || (x + height - 1 == 19 && y + width - 1 == 19 && tempTransfer.size() == width * height)) return true;
		else return false;
	}
	else
	{
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				if (count == total)break;
				else if (board[x][y]->getOwner() != 0 && tempTransfer.front() != 0) return false;
				else if (tempTransfer.front() == 0) {
					tempTransfer.erase(tempTransfer.begin());
					y++;
					continue;
				}
				else
				{
					count++;
					if (x != 0 && y != 0 && x != 19 && y != 19){
						if ((board[x + 1][y]->getOwner() == owner || board[x][y + 1]->getOwner() == owner || board[x - 1][y]->getOwner() == owner || board[x][y - 1]->getOwner() == owner)) return false;
						else if (board[x - 1][y - 1]->getOwner() == owner || board[x - 1][y + 1]->getOwner() == owner || board[x + 1][y - 1]->getOwner() == owner || board[x + 1][y + 1]->getOwner() == owner)isPlaceable = true;
					}
					else {
						if (x == 0) {
							if ((board[x + 1][y]->getOwner() == owner || board[x][y + 1]->getOwner() == owner || board[x][y - 1]->getOwner() == owner)) return false;
							else if (board[x + 1][y - 1]->getOwner() == owner || board[x + 1][y + 1]->getOwner() == owner)isPlaceable = true;
						}
						else if (y == 0) {
							if ((board[x + 1][y]->getOwner() == owner || board[x][y + 1]->getOwner() == owner || board[x - 1][y]->getOwner() == owner)) return false;
							else if (board[x - 1][y + 1]->getOwner() == owner || board[x + 1][y + 1]->getOwner() == owner)isPlaceable = true;
						}
						else if (x == 19) {
							if ((board[x][y + 1]->getOwner() == owner || board[x - 1][y]->getOwner() == owner || board[x][y - 1]->getOwner() == owner)) return false;
							else if (board[x - 1][y - 1]->getOwner() == owner || board[x - 1][y + 1]->getOwner() == owner)isPlaceable = true;
						}
						else
						{
							if ((board[x + 1][y]->getOwner() == owner || board[x - 1][y]->getOwner() == owner || board[x][y - 1]->getOwner() == owner)) return false;
							else if (board[x - 1][y - 1]->getOwner() == owner || board[x + 1][y - 1]->getOwner() == owner)isPlaceable = true;
						}
					}
				}
				tempTransfer.erase(tempTransfer.begin());
				y++;
			}
			y = posY;
			x++;
		}
		return isPlaceable;
	}
}
int checkPayoff(int paraX, int paraY, block* par) {
	vector<int> tempTransfer = par->getBlock();
	int count = 0, total = par->getNum(), x = paraX, y = paraY, id = par->getID(), payoff = 0, owner = par->getOwner();
	for (size_t i = 0; i < par->getY(); i++)
	{
		for (size_t j = 0; j < par->getX(); j++)
		{

			if (count == total)break;
			else if (tempTransfer.front() != 0)
			{
				if (x > 0 && x < 19 && y>0 && y < 19) {
					if (board[x - 1][y - 1]->getOwner() != owner && board[x - 1][y - 1]->getOwner() != 0)payoff++;
					if (board[x - 1][y + 1]->getOwner() != owner && board[x - 1][y + 1]->getOwner() != 0)payoff++;
					if (board[x + 1][y - 1]->getOwner() != owner && board[x + 1][y - 1]->getOwner() != 0)payoff++;
					if (board[x + 1][y + 1]->getOwner() != owner && board[x + 1][y + 1]->getOwner() != 0)payoff++;
				}
				else {
					if (x == 0) {
						if (board[x + 1][y - 1]->getOwner() != owner && board[x + 1][y - 1]->getOwner() != 0)payoff++;
						if (board[x + 1][y + 1]->getOwner() != owner && board[x + 1][y + 1]->getOwner() != 0)payoff++;
					}
					else if (y == 0) {
						if (board[x - 1][y + 1]->getOwner() != owner && board[x - 1][y + 1]->getOwner() != 0)payoff++;
						if (board[x + 1][y + 1]->getOwner() != owner && board[x + 1][y + 1]->getOwner() != 0)payoff++;
					}
					else if (x == 19) {
						if (board[x - 1][y - 1]->getOwner() != owner && board[x - 1][y - 1]->getOwner() != 0)payoff++;
						if (board[x - 1][y + 1]->getOwner() != owner && board[x - 1][y + 1]->getOwner() != 0)payoff++;
					}
					else {
						if (board[x - 1][y - 1]->getOwner() != owner && board[x - 1][y - 1]->getOwner() != 0)payoff++;
						if (board[x + 1][y - 1]->getOwner() != owner && board[x + 1][y - 1]->getOwner() != 0)payoff++;
					}
				}
				count++;
			}
			tempTransfer.erase(tempTransfer.begin());
			y++;
		}
		y = paraY;
		x++;
	}
	return payoff;
}
void checkPayoff(int paraX, int paraY, block* par, vector<square*> interlopers) {
	vector<int> tempTransfer = par->getBlock();
	int count = 0, total = par->getNum(), x = paraX, y = paraY, id = par->getID(), payoff = 0, owner = par->getOwner();
	plan* newPlan = nullptr;
	for (size_t i = 0; i < par->getY(); i++)
	{
		for (size_t j = 0; j < par->getX(); j++)
		{

			if (count == total)break;
			else if (tempTransfer.front() != 0)
			{
				for (auto it : interlopers) {
					if (x == it->getX() && y == it->getY())payoff++;
				}
				count++;
			}
			tempTransfer.erase(tempTransfer.begin());
			y++;
		}
		y = paraY;
		x++;
	}
	if (payoff > 0) {
		newPlan = new plan(paraX, paraY, payoff,par);
		playerSet.at(owner - 1)->addPlan(newPlan);
	}
	newPlan = nullptr;
	//delete newPlan;
}
void RecordAvailbleSquares(int x, int y, int width, int height,int skipedPlayer) {
	int owner = 0;
	for (auto it : playerSet)it->cleanSquaresRecord();
	for (int i = x; i < height; i++)
	{
		for (int j = y; j < width; j++)
		{
			int owner = 0;
			if ((i == 0 && j == 0) || (i == 0 && j == 19) || (i == 19 && j == 0) || (i == 19 && j == 19)) continue;
			else if (board[i][j]->getOwner() != 0)continue;
			else if (i == 0) {
				if ((board[i + 1][j]->getOwner() != 0) || (board[i][j + 1]->getOwner() != 0) || (board[i][j - 1]->getOwner() != 0)) continue;
				else 
				{ 
					if (board[i + 1][j - 1]->getOwner() != 0)playerSet.at(board[i + 1][j - 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
					else if (board[i + 1][j + 1]->getOwner() != 0)playerSet.at(board[i + 1][j + 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
				}
			}
			else if (j == 0) {
				if ((board[i + 1][j]->getOwner() != 0) || (board[i][j + 1]->getOwner() != 0) || (board[i - 1][j]->getOwner() != 0)) continue;
				else 
				{ 
					if (board[i - 1][j + 1]->getOwner() != 0)playerSet.at(board[i - 1][j + 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
					else if (board[i + 1][j + 1]->getOwner() != 0)playerSet.at(board[i + 1][j + 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
				}
			}
			else if (i == 19) {
				if ((board[i][j + 1]->getOwner() != 0) || (board[i - 1][j]->getOwner() != 0) || (board[i][j - 1]->getOwner() != 0)) continue;
				else 
				{ 
					if (board[i - 1][j + 1]->getOwner() != 0)playerSet.at(board[i - 1][j + 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
					else if (board[i - 1][j - 1]->getOwner() != 0)playerSet.at(board[i - 1][j - 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
				}
			}
			else if (j == 19) {
				if ((board[i + 1][j]->getOwner() != 0) || (board[i - 1][j]->getOwner() != 0) || (board[i - 1][j]->getOwner() != 0)) continue;
				else 
				{ 
					if (board[i - 1][j - 1]->getOwner() != 0)playerSet.at(board[i - 1][j - 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
					else if (board[i + 1][j - 1]->getOwner() != 0)playerSet.at(board[i + 1][j - 1]->getOwner() - 1)->setAvailableSquare(board[i][j]);
				}
			}
			else {
				//if ((board[i + 1][j]->getOwner() != 0) || (board[i - 1][j]->getOwner() != 0) || (board[i][j + 1]->getOwner() != 0) || (board[i][j - 1]->getOwner() != 0)) continue;
				
 
					owner = board[i - 1][j - 1]->getOwner();
					if (owner != 0)
						if ((board[i + 1][j]->getOwner() != owner) && (board[i - 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner))
							playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
					owner = board[i - 1][j + 1]->getOwner();
					if (owner != 0) 
						if ((board[i + 1][j]->getOwner() != owner) && (board[i - 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner))
							playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
					owner = board[i + 1][j - 1]->getOwner();
					if (owner != 0)
						if ((board[i + 1][j]->getOwner() != owner) && (board[i - 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner))
							playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
					owner = board[i + 1][j + 1]->getOwner();
					if (owner != 0)
						if ((board[i + 1][j]->getOwner() != owner) && (board[i - 1][j]->getOwner() != owner) && (board[i][j + 1]->getOwner() != owner) && (board[i][j - 1]->getOwner() != owner))
							playerSet.at(owner - 1)->setAvailableSquare(board[i][j]);
			}
		}
	}
}
vector<square*> getRelativeLocation(int x, int y, block* target) {
	bool squaresDetected[4] = { 0 };
	int width = target->getX(), height = target->getY(), type = target->getID(), playerID = target->getOwner(), count = 0;
	vector<int> temp = target->getBlock();
	vector<square*> availableSquares;
	if (x == 0 || y == 0 || x == 19 || y == 19) count = 2;
	else {
		if (board[x - 1][y - 1]->getOwner() == playerID)squaresDetected[0] = true;
		else if (board[x - 1][y + 1]->getOwner() == playerID)squaresDetected[1] = true;
		else if (board[x + 1][y + 1]->getOwner() == playerID)squaresDetected[2] = true;
		else if (board[x - 1][y + 1]->getOwner() == playerID)squaresDetected[3] = true;
		int count = 0;
		for (auto it : squaresDetected)
			if (it) count++;
	}
	if (!(count > 2 || (squaresDetected[0] && squaresDetected[2]) || (squaresDetected[1] && squaresDetected[3]))) {
		int index = 0;
		for (int i = 0; i < height; i++) {
			if (count == target->getNum())break;
			for (int j = 0; j < width; j++) {
				if (temp.at(index) != 0) {
					count++;
					if (isPlaceable(target, x - j, y - i)) availableSquares.push_back(board[x - j][y - i]);
				}
			}
		}
	}
	//if (availableSquares.size() > 0) {
	//	if (availableSquares.size() == 1)return availableSquares;
	//	else {
	//		int adjacentSquaresCount = 0;
	//		int index = 0;
	//		for (auto it:availableSquares) {
	//			x = it->getX();
	//			y = it->getY();
	//			for (int i = 0; i < height; i++) {
	//				for (int j = 0; j < width; j++) {
	//					if (temp.at(index) != 0) {
	//						if (board[x + i - 1][y + j - 1]->getOwner() != 0)adjacentSquaresCount++;
	//					}
	//						
	//				}
	//			}
	//		}
	//	}
	//}
	if (availableSquares.size() > 0) return availableSquares;
	else return vector<square*>{board[x][y]};
}
bool humanPlacement(int parax, int paray, block* target) {
	int width = target->getX(), height = target->getY(), x = 0, y = 0, cmd = 0;
	vector<square*> temp = getRelativeLocation(parax, paray, target);
	if (temp.size() == 1) {
		if (!isPlaceable(target, temp.front()->getX(), temp.front()->getY())) {
			cout << "This location is illegal, reinput a new location" << endl;
			return false;
		}
	}
	cout << "These placement are available for you:" << endl;
	for(int i = 0; i < temp.size();i++) {
		x = temp.at(i)->getX();
		y = temp.at(i)->getY();
		putBlock(x, y,target,false);
		cout << i + 1 << ':' << endl;
		displayBoard(parax-2,paray-2,width+paray+2,height+parax+2);
		putBlock(x, y, target, true);
	}
	if (temp.size() > 0) {
		cin >> cmd;
		putBlock(temp.at(cmd - 1)->getX(), temp.at(cmd - 1)->getY(), target,false);
		playerSet.front()->putBlock(target->getID()-1);
		return true;
	}
	return false;
}
void AI(player* aiPlayer) {
	int id = aiPlayer->getID(), direction = 0, randNum = 0, x = 0, y = 0, owner=aiPlayer->getID();
	vector<block*> blocks = aiPlayer->getRemainingBlocks();
	bool hasBeenPlaced = false;
	block* pTempBlock = nullptr;
	if (turn == 1) {
		while (randNum == 11 || randNum <= 4 || randNum == 10 || randNum < 6)
		{
			randNum = rand() % 20;
		}
		pTempBlock = aiPlayer->getBlock(randNum);
		//cout << "Player " << id << " Rand: " << randNum << endl;
		//if (pTempBlock->getSymmetry())count = 3;
		//else count = 6;
		for (int i = 0; i < 8; i++)
		{
			switch (id)
			{
			case 1:
				x = y = 0;
				break;
			case 2:
				x = 0;
				y = 19 - (pTempBlock->getX() - 1);
				break;
			case 3:
				x = 19 - (pTempBlock->getY() - 1);
				y = 0;
				break;
			case 4:
				x = 19 - (pTempBlock->getY() - 1);
				y = 19 - (pTempBlock->getX() - 1);
				break;
			default:
				cout << "Exception in AIplayers'ID" << endl;
				break;
			}
			if (isPlaceable(pTempBlock, x, y)) {
				putBlock(x, y, pTempBlock,false);
				aiPlayer->putBlock(randNum-1);
				pTempBlock = nullptr;
				break;
			}
			else if(i<4) pTempBlock->rotate(true);
			else
			{
				pTempBlock->rotate(true);
				pTempBlock->reverse();
			}
		}
	}
	else
	{
		vector<square*> availableSquares = aiPlayer->getAvailableSquares();
		vector<int> payoffs;
		if (availableSquares.empty()) {
			aiPlayer->passed();
		}
		else {
			int terrX = availableSquares.back()->getX(), terrY = availableSquares.back()->getY(), minX = 19, minY = 19;
			bool interlopers[4] = { false };
			vector<square*> pridictionsForOthers;
			dataset paras = aiPlayer->getParameters();
			for (int i = paras.origin_x; i != terrX; i += paras.kx) {
				for (int j = paras.origin_y; j != terrY; j += paras.ky) {
					if (board[i][j]->getOwner() != owner && board[i][j]->getOwner() != 0) {
						interlopers[board[i][j]->getOwner() - 1] = true;
						if (board[i][j]->getX() < minX)minX = board[i][j]->getX();
						if (board[i][j]->getY() < minY)minY = board[i][j]->getY();
					}
				}
			}
			x = fmin(paras.origin_x, terrX);
			y = fmin(paras.origin_y, terrY);
			vector<square*> requiredIndex;
			for (int i = 0; i < 4;i++) {
				if (interlopers[i]) { 
					requiredIndex = playerSet.at(i)->getAvailableSquares(x,y,fabs(paras.origin_y-terrY),fabs(paras.origin_x - terrX));
					for (auto it : requiredIndex) {
						pridictionsForOthers.push_back(it);
					}
				}
			}
			bool haveInterlopers = !pridictionsForOthers.empty();
			if (haveInterlopers) {
				cout << "There are innterlopers for player " << id << endl;
			}
			else {
				for (int i = 0; i < 4; i++) {
					if (i == id - 1)continue;
					requiredIndex = playerSet.at(i)->getAvailableSquares();
					for (auto it : requiredIndex) {
						pridictionsForOthers.push_back(it);
					}
				}
			}
			for (int i = blocks.size() - 1; i >= 0; i--) {
				pTempBlock = aiPlayer->getBlock(i);
				for (vector<square*>::reverse_iterator rit = availableSquares.rbegin(); rit != availableSquares.rend(); ++rit) {
					if (hasBeenPlaced)break;
					x = (*rit)->getX();
					y = (*rit)->getY();
					vector<square*> temp = getRelativeLocation(x, y, pTempBlock);
					int count = 0;
					if (pTempBlock->getSymmetry()) count = 4;
					else count = 8;
						for (auto it : temp) {
							x = it->getX();
							y = it->getY();
							for (int k = 0; k < count; k++) {
								if (isPlaceable(pTempBlock, x, y))
								{
									checkPayoff(x, y, pTempBlock, pridictionsForOthers);
								}
								else if (k < 4) pTempBlock->rotate(true);
								else if (k >= 4)
								{
									pTempBlock->rotate(true);
									pTempBlock->reverse();
								}
								else break;
							}
						}
				}
			}
			vector<plan*> plans=aiPlayer->getPlans();
			//plan *pPlan = nullptr;
			if (!plans.empty()) {
				int maxPayoff = 0;
				for (int i = 0; i < plans.size();i++) {
					if (plans.at(i)->getPayoff() > maxPayoff)
						maxPayoff = plans.at(i)->getPayoff();
					else if (plans.at(i)->getPayoff() < maxPayoff) {
						plans.erase(plans.begin() + i);
					}
				}
				cout << "p" << id << "  plans size: " << plans.size() << endl;
				if (plans.size() > 1) {
					vector<plan*> buffer;
					buffer.push_back(plans.front());
					//pPlan = plans.front();
					for (int i = 1; i < plans.size();i++) {
						bool isTheSamePlan = false;
						for (int j = 0; j < buffer.size();j++) {
							if (plans.at(i)->equaulsTo(buffer.at(j))) {
								isTheSamePlan = true;
								buffer.at(j)->foundSamePlan();
							}
							if (j == buffer.size() - 1) {
								if (!isTheSamePlan) {
									buffer.push_back(plans.at(i));
								}
							}	
						}
					}
					cout << "p" << id << "  buffer size: " << buffer.size() << endl;
					if (buffer.size() > 1) {
						vector<plan*> selectedPlans;
						int maxPayoff = 0, curr_payoff=0;
						for (auto it : buffer) {
							curr_payoff = it->getPayoff();
							if (curr_payoff > maxPayoff) {
								maxPayoff = curr_payoff;
							}
						}
						for (auto it : buffer) {
							curr_payoff = it->getPayoff();
							if (curr_payoff == maxPayoff) {
								selectedPlans.push_back(it);
							}
						}
						if (selectedPlans.size() > 1) {
							int maxNumOfSamePlan = 0;
							vector<plan*> finalPlan;
							cout <<"Selcted size: " <<selectedPlans.size()<<endl;
							for (auto it:selectedPlans) {
								cout <<"payoff: "<< it->getPayoff() <<" numOfSamePlan:"<< it->getNumOfSamePlan() << endl;
								if (it->getNumOfSamePlan() > maxNumOfSamePlan) maxNumOfSamePlan=it->getNumOfSamePlan();
							}
							for (auto it : selectedPlans) {
								if (it->getNumOfSamePlan() == maxNumOfSamePlan) finalPlan.push_back(it);
							}
							if (finalPlan.size() > 1) {
								int random_plan = rand() % (finalPlan.size() - 1);
								x = finalPlan.at(random_plan)->getX();
								y = finalPlan.at(random_plan)->getY();
								pTempBlock = finalPlan.at(random_plan)->getTile();
								if (isPlaceable(pTempBlock, x, y)) {
									putBlock(x, y, pTempBlock, false);
									aiPlayer->putSpecificBlock(pTempBlock);
									pTempBlock = nullptr;
									hasBeenPlaced = true;
								}
							}
							else {
								x = finalPlan.front()->getX();
								y = finalPlan.front()->getY();
								pTempBlock = finalPlan.front()->getTile();
								if (isPlaceable(pTempBlock, x, y)) {
									putBlock(x, y, pTempBlock, false);
									aiPlayer->putSpecificBlock(pTempBlock);
									pTempBlock = nullptr;
									hasBeenPlaced = true;
								}

							}
						}
					}
					//cout << "p" << id << "  (After) plans size: " << plans.size() << endl;
					
				}
				else {
					x = plans.front()->getX();
					y = plans.front()->getY();
					pTempBlock = plans.front()->getTile();
					if (isPlaceable(pTempBlock, x, y)) {
						putBlock(x, y, pTempBlock, false);
						aiPlayer->putSpecificBlock(pTempBlock);
						pTempBlock = nullptr;
						hasBeenPlaced = true;
					}
				}
				
			}
			if (!hasBeenPlaced) {
				//cout << "Player " << id << " chooses the basic strategy" << endl;
				//aiPlayer->clearPlans();
				//plans.clear();
				//int typeCount[5] = { 0 };
				//for (auto it : blocks) {
				//	switch (it->getNum())
				//	{
				//	case 1:
				//		typeCount[0]++;
				//		break;
				//	case 2:
				//		typeCount[1]++;
				//		break;
				//	case 3:
				//		typeCount[2]++;
				//		break;
				//	case 4:
				//		typeCount[3]++;
				//		break;
				//	case 5:
				//		typeCount[4]++;
				//		break;
				//	default:
				//		break;
				//	}
				//}
				//int tot_size = blocks.size(), a, b, levels;
				//plan* newPlan = nullptr;
				//if (typeCount[4] != 0 || typeCount[3] != 0) {
				//	a = 4;
				//	b = 3;
				//	levels = 2;
				//}
				//else if (typeCount[2] != 0 || typeCount[1] != 0) {
				//	a = 2;
				//	b = 1;
				//	levels = 1;
				//}
				//else {
				//	a = 0;
				//	b = 0;
				//	levels = 0;
				//}
				//for (int h = 0; h < levels; h++) {
				//	for (int i = tot_size - 1; i >= tot_size - typeCount[a] - typeCount[b] - 1; i--) {
				//		if (hasBeenPlaced) break;
				//		pTempBlock = aiPlayer->getBlock(i);
				//		for (vector<square*>::reverse_iterator rit = availableSquares.rbegin(); rit != availableSquares.rend(); ++rit) {
				//			x = (*rit)->getX();
				//			y = (*rit)->getY();
				//			vector<square*> temp = getRelativeLocation(x, y, pTempBlock);
				//			for (auto it : temp) {
				//				x = it->getX();
				//				y = it->getY();
				//				int count = 0;
				//				if (pTempBlock->getSymmetry()) count = 4;
				//				else count = 8;
				//				for (int k = 0; k < count; k++) {
				//					if (isPlaceable(pTempBlock, x, y))
				//					{
				//						newPlan = new plan(x, y, pTempBlock);
				//						aiPlayer->addPlan(newPlan);
				//					}
				//					else if (k < 4) pTempBlock->rotate(true);
				//					else if (k >= 4)
				//					{
				//						pTempBlock->rotate(true);
				//						pTempBlock->reverse();
				//					}
				//					else break;
				//				}
				//			}
				//		}
				//	}
				//	plans = aiPlayer->getPlans();
				//	if (!plans.empty()) {
				//		if (plans.size() > 1) {
				//			int random_plan = rand() % (plans.size() - 1);
				//			x = plans.at(random_plan)->getX();
				//			y = plans.at(random_plan)->getY();
				//			pTempBlock = plans.at(random_plan)->getTile();
				//			putBlock(x, y, pTempBlock, false);
				//			aiPlayer->putSpecificBlock(pTempBlock);
				//			pTempBlock = nullptr;
				//			hasBeenPlaced = true;
				//		}
				//		else {
				//			x = plans.front()->getX();
				//			y = plans.front()->getY();
				//			pTempBlock = plans.front()->getTile();
				//			putBlock(x, y, pTempBlock, false);
				//			aiPlayer->putSpecificBlock(pTempBlock);
				//			pTempBlock = nullptr;
				//			hasBeenPlaced = true;
				//		}
				//	}
				//	else {
				//		if (h == 0) {
				//			a -= 2;
				//			b -= 2;
				//		}

				//	}
				//}

				
				for (int j = blocks.size() - 1; j >= 0; j--) {
					if (hasBeenPlaced)break;
					pTempBlock = aiPlayer->getBlock(j);
					for (vector<square*>::reverse_iterator rit = availableSquares.rbegin(); rit != availableSquares.rend(); ++rit) {
						if (hasBeenPlaced)break;
						x = (*rit)->getX();
						y = (*rit)->getY();
						vector<square*> temp = getRelativeLocation(x, y, pTempBlock);
						int size = temp.size();
						if (size > 1) {
							int maxPayoff = 0;
							for (auto it : temp) {
								int currentPayoff = checkPayoff(it->getX(), it->getY(), pTempBlock);
								if (currentPayoff >= maxPayoff) {
									maxPayoff = currentPayoff;
									x = it->getX();
									y = it->getY();
								}
							}
						}
						else {
							x = temp.front()->getX();
							y = temp.front()->getY();
						}
						int count = 0;
						if (pTempBlock->getSymmetry()) count = 4;
						else count = 8;
						for (int k = 0; k < count; k++) {
							if (isPlaceable(pTempBlock, x, y))
							{
								putBlock(x, y, pTempBlock, false);
								aiPlayer->putBlock(j);
								pTempBlock = nullptr;
								hasBeenPlaced = true;
								break;
							}
							else if (k < 4) pTempBlock->rotate(true);
							else if (k >= 4)
							{
								pTempBlock->rotate(true);
								pTempBlock->reverse();
							}
							else break;
						}
					}
				}
			}
			if (!hasBeenPlaced) {
				cout << "Player " << id << ", " << aiPlayer->getName() << " is Passed" << endl;
				aiPlayer->passed();
			}
			aiPlayer->clearPlans();
			//for (int i = availableSquares.size() - 1; i >= 0; i--) {
			//	x = availableSquares.at(i)->getX();
			//	y = availableSquares.at(i)->getY();
			//	int a = 4;
			//	for (; a >= 0; a--) {
			//		if (x + a <= 19 && x - a >= 0 && y + a <= 19 && y - a >= 0) break;
			//	}
			//	if (x + 3 <= 19 && x - 3 >= 0 && y + 3 <= 19 && y - 3 >= 0) a = 3;
			//	else {
			//		if (x + 2 <= 19 && x - 2 >= 0 && y + 2 <= 19 && y - 2 >= 0) a = 2;
			//		else {
			//			if (x + 1 <= 19 && x - 1 >= 0 && y + 1 <= 19 && y - 1 >= 0) a = 1;
			//			else a = 0;
			//		}
			//	}
			//	cout << "player" << id << " a: " << a << endl;
			//	int xrecord = x;
			//	while (a > 0) {
			//		if (a = 4) {

			//		}
			//		for (int j = x - a; j < x + a - 1; j++) {
			//			if (hasBeenPlaced)break;
			//			for (int k = y - a; k < y + a - 1; k++) {
			//				if (hasBeenPlaced)break;
			//				cout << "player " << owner << "j:" << j << "k:" << k << endl;
			//				if (board[j][k]->getOwner() != 0 && board[j][k]->getOwner() != id) {
			//					for (vector<block*>::reverse_iterator rit = blocks.rbegin(); rit != blocks.rend(); ++rit) {
			//						if (hasBeenPlaced)break;
			//						if ((*rit)->getX() == a + 1 || (*rit)->getY() == a + 1)
			//						{
			//							pTempBlock = (*rit);
			//							for (int l = 0; l < 8; l++) {
			//								if (hasBeenPlaced)break;
			//								vector<square*> temp = getRelativeLocation(x, y, pTempBlock);
			//								for (auto it : temp) {
			//									x = it->getX();
			//									y = it->getY();
			//									if (putBlock(x, y, pTempBlock) > 0) {
			//										putBlock(x, y, pTempBlock, false);
			//										aiPlayer->putBlock(i);
			//										pTempBlock = nullptr;
			//										hasBeenPlaced = true;
			//										break;
			//									}
			//								}
			//								if (l < 4) pTempBlock->rotate(true);
			//								else if (l >= 4)
			//								{
			//									pTempBlock->rotate(true);
			//									pTempBlock->reverse();
			//								}
			//								else break;
			//							}
			//						}
			//					}
			//				}
			//			}
			//		}
			//		a--;
			//	}
			//}



		//if (!hasBeenPlaced) {

		//	if (!hasBeenPlaced) {
	


		//		//for (int i = blocks.size() - 1; i >= 0; i--)
		//		//{
		//		//	if (hasBeenPlaced)break;

		//		//	pTempBlock = blocks.at(i);

		//		//}
		//		//if (typeCount[4] > 0 || typeCount[3] > 0) {
		//		//	for (int i = blocks.size() - 1; i >= blocks.size() - typeCount[4] - typeCount[3] - 1; i--) {
		//		//		for (int j = availableSquares.size() - 1; j >= 0; j--) {

		//		//		}
		//		//	}
		//		//}
		//		//else if (typeCount[2] > 0 || typeCount[1] > 0) {
		//		//	for (int i = blocks.size() - 1; i >= blocks.size() - typeCount[2] - typeCount[1] - 1; i--) {
		//		//		for (int j = availableSquares.size() - 1; j >= 0; j--) {

		//		//		}
		//		//	}
		//		//}
		//		//if (!hasBeenPlaced) {
		//		//	for (int i = availableSquares.size() - 1; i >= 0; i--) {
		//		//		if (typeCount[2] > 0 || typeCount[1] > 0) {
		//		//			for (int i = blocks.size() - 1; i >= blocks.size() - -typeCount[4] - typeCount[3] - typeCount[2] - typeCount[1] - 1; i--) {

		//		//			}
		//		//		}
		//		//	}
		//		//}
		//		//if (!hasBeenPlaced) {
		//		//	pTempBlock = blocks.front();
		//		//	for (int i = availableSquares.size() - 1; i >= 0; i--) {
		//		//		if (isPlaceable(pTempBlock, x, y))
		//		//		{
		//		//			putBlock(x, y, pTempBlock, false);
		//		//			aiPlayer->putBlock(i);
		//		//			pTempBlock = nullptr;
		//		//			hasBeenPlaced = true;
		//		//			break;
		//		//		}
		//		//	}
		//		//}
		//	}
		//}
		}

	}
}
void humanTurn() {
	player* human;
	human = new player(1, "Human");
	cout << "\tHuman Player's Turn" << endl;
	int cmd = 0;
	human->displayRemainingBlocks();
	cout << "\tChoose the tile you prefer to place." << endl;
	cin >> cmd;
	block* target = human->getBlock(cmd);
	cout << "\tDo you want to rotate it or flip it?" << endl;
	cout << "\t1.Rotate\t2.Flip\t3.Put Directly" << endl;
	cin >> cmd;
	switch (cmd)
	{
	case 1:
		cout << "\t1.Clockwise Rotation\t2.Counterclockwise Rotation" << endl;
		cin >> cmd;
		if (cmd == 1)
		{
			cout << "\t1.What degree do you prefer to" << endl;
			cout << "\t1. 90\t2. 180\t3. 270" << endl;
			cin >> cmd;
			for (size_t i = 0; i < cmd; i++)
			{
				target->rotate(false);
			}

		}
		else
		{
			cout << "\t1.What degree do you prefer to" << endl;
			cout << "\t1. 90\t2. 180\t3. 270" << endl;
			cin >> cmd;
			for (size_t i = 0; i < cmd; i++)
			{
				target->rotate(true);
			}

		}
		cout << "Result:" << endl;
		target->displayBlock();
		break;
	case 2:
		target->reverse();
		cout << "Result:" << endl;
		target->displayBlock();
		break;
	case 3:
		break;
	default:
		cout << "Wrong input" << endl;
		break;
	}
	cout << "where would you like to place?" << endl;
	int x, y = 0;
	cin >> x >> y;
	cout << "x:" << x << "y:" << x << endl;
	//put(target, x, y);
	//displayBoard();
	delete human;
	delete target;
}
//bool canPlaceTiles(block* tile, int posX, int posY) {
//	int count = 0, x = posX - 1, y = posY - 1, width = tile->getX(), height = tile->getY(), total = tile->getNum(), owner = tile->getOwner();
//	vector<int> tempTransfer = tile->getBlock();
//	if (x + height > 19 || y + width > 19 || x < 0 || y < 0) return false;
//	for (size_t i = 0; i < height; i++)
//	{
//		for (size_t j = 0; j < width; j++)
//		{
//			if (count == total)break;
//			else if (board[x][y]->getOwner() != 0 && tempTransfer.front() != 0) return false;
//			else if (tempTransfer.front() == 0) {
//				tempTransfer.erase(tempTransfer.begin());
//				y++;
//				continue;
//			}
//			else
//			{
//				count++;
//				if ((x == 0 && y == 0) || (x == 0 && y + width - 1 == 19) || (x + height - 1 == 19 && y == 0) || (x + height - 1 == 19 && y + width - 1 == 19)) return true;
//				else if (x == 0 || y == 0 || x + height - 1 == 19 || y + width - 1 == 19)continue;
//				else if ((board[x + 1][y]->getOwner() == owner || board[x][y + 1]->getOwner() == owner || board[x - 1][y]->getOwner() == owner || board[x][y - 1]->getOwner() == owner)) return false;
//			}
//			tempTransfer.erase(tempTransfer.begin());
//			y++;
//		}
//		y = posY - 1;
//		x++;
//	}
//	x = posX - 2, y = posY - 2;
//	for (size_t i = 0; i < height; i++)
//	{
//		for (size_t j = 0; j < width; j++) {
//			if ((x > posX - 2 && x < posX - 3 + height) && (y > posY - 2 && y < posY - 3 + width))continue;
//			else if (board[x][y]->getOwner() == owner) return true;
//			y++;
//		}
//		y = posY - 2;
//		x++;
//	}
//	return false;
//}





