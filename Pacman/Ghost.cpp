#include "Ghost.h"
#include "curses.h"
#include <random>
#include <time.h>
#include <functional>

int Ghost::rollDirection(char ** map) {
	//TODO: powinien mniej losowo siê przemieszczaæ
	int rng;
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(1, 4);
	rng = distribution(generator);
	return rng;
}

void Ghost::moveEnemy(char ** map) {
	//Przemieszcza duszka
	direction = this->rollDirection(map);
	this->checkCollision(map);
	if (posX > 1 && posX < 28 && posY > 1 && posY < 27 && collision == false) {
		if (direction == 1) posX--;
		if (direction == 2) posY--;
		if (direction == 3) posX++;
		if (direction == 4) posY++;
	}
}

void Ghost::displayEnemy() {
	mvprintw(posY, posX + 35, "&");
}

void Ghost::checkCollision(char ** map) {
	char elementE;
	if (direction == 1) elementE = map[posX - 1][posY];
	if (direction == 2) elementE = map[posX][posY - 1];
	if (direction == 3) elementE = map[posX + 1][posY];
	if (direction == 4) elementE = map[posX][posY + 1];
	if (elementE == '#') collision = true;
	else collision = false;
}