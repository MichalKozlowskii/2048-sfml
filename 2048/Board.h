#pragma once 
#include  "SFML/Graphics.hpp" 
#include "Node.h"
#include <list>

using namespace std;

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Board {
private:
	list<Node> grid;
	sf::RenderWindow window;
	bool canMove = true;
	void setup();
	void fillGrid();
	void spawnTile();
	void drawUI();
	void drawWinScreen();
	void drawLooseScreen();
	int getScore();
	void move(Direction dir);
	bool hasWon();
	bool isAbleToMove();
	bool hasLost();
public:
	Board();
	void captureKeyboardInput();
	void refresh();
};