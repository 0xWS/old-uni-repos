#pragma once

#include <random>
#include <iostream>

class Ghost {
private:
	bool collision = false;
	int posX = 13;
	int posY = 9;
	int direction = 1; //1- lewo, 2- góra, 3- prawo, 4- dó³
	void checkCollision(char ** map);
	int rollDirection(char ** map);
public:
	void moveEnemy(char ** map);
	void displayEnemy();
	
	int getEnemyPosX() { return posX; }
	int getEnemyPosY() { return posY; }
};