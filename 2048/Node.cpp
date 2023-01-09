#include "Node.h"

Node::Node(int x, int y, int state) {
	this->x = x;
	this->y = y;
	this->state = state;
	this->posX = 15 + 147 * (x-1);
	this->posY = 119 + 147 * (y - 1);
}

int Node::getX() {
	return this->x;
}

int Node::getY() {
	return this->y;
}

int Node::getPosX() {
	return this->posX;
}

int Node::getPosY() {
	return this->posY;
}

int Node::getState() {
	return this->state;
}

bool Node::getSpawnedStatus() {
	return this->wasSpawned;
}

void Node::setX(int x) {
	this->x = x;
}

void Node::setY(int y) {
	this->y = y;
}

void Node::setState(int newState) {
	this->state = newState;
}

void Node::setSpawnStatus(bool spawnState) {
	this->wasSpawned = spawnState;
}

void Node::insert(std::list<Node>& l, int xSearch, int ySearch, int new_state) {
	for (auto it = l.rbegin(); it != l.rend(); it++) {
		if (it->x == xSearch && it->y == ySearch) {
			it->state = new_state;
			return;
		}
	}
}
