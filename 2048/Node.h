#pragma once
#include <list>

class Node {
private:
	int x, y, state, posX, posY;
	bool wasSpawned = false;
public:
	Node(int x, int y, int state);	
	int getX();
	int getY();
	int getPosX();
	int getPosY();
	int getState();
	bool getSpawnedStatus();
	void setX(int x);
	void setY(int y);
	void setState(int newState);
	void setSpawnStatus(bool spawnState);
	void insert(std::list<Node>& l, int xSearch, int ySearch, int new_state);
};