#pragma once

#include "pch.h"
#include <vector>

class Player {
private:
	const bool DEV_MODE = true;
	const double COMBO_BONUS = 2;
	const int DEFAULT_POSX = 13;
	const int DEFAULT_POSY = 17;

	bool collision = false;
	bool superpowerFlag = false;
	int posX = DEFAULT_POSX;
	int posY = DEFAULT_POSY;
	direction pDirection = left;
	int speed = 1;
	int score = 0;
	double scoreCombo = 1;
	short health = 3;

	void checkCollision(char ** map);
	void addPoints();
	void superpower();
public:
	void setPlayerDirection(direction ch);
	void movePlayer(char ** map);
	void displayPlayer();
	void enemyHit(int x, int y);

	int checkElement(char ** map);
	void displayStats();
};