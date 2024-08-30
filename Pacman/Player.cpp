#include "Player.h"
#include "curses.h"
#include "pch.h"
#include <string>
#include <cstring>
#include <charconv>
#include <vector>

void Player::setPlayerDirection(direction ch) {
		if(ch != direction::none) pDirection = ch;
}

void Player::movePlayer(char ** map) {
	//Przemieszcza gracza w zale¿noœci od kierunku
	this->checkCollision(map);
	if (posX > 0 && posX < 29 && posY > 0 && posY < 28 && collision == false) {
		if (pDirection == direction::left) posX-=speed;
		if (pDirection == direction::up) posY-=speed;
		if (pDirection == direction::right) posX+=speed;
		if (pDirection == direction::down) posY+=speed;
	}
}

void Player::displayPlayer() {
	std::string playerSprite;
	if (pDirection == direction::left) playerSprite = '<';
	if (pDirection == direction::up) playerSprite = '^';
	if (pDirection == direction::right) playerSprite = '>';
	if (pDirection == direction::down) playerSprite = 'v';
	mvprintw(posY, posX+35, playerSprite.c_str());
}

int Player::checkElement(char ** map) {
	//Funkcja która informuje o tym na jakim polu znajduje siê gracz
	char element = map[posX][posY];
	if (element == ' ') {
		scoreCombo = 1;
		return 0;
	}
	if (element == '*') {
		this->addPoints();
		map[posX][posY] = ' ';
		return 1;
	}
	//if (element == '$') return 2;
	//if (element == 'o') return 3;
	return 0;
}

void Player::checkCollision(char ** map) {
	char elementC = ' ';
	if (pDirection == direction::left) elementC = map[posX - 1][posY];
	if (pDirection == direction::up) elementC = map[posX][posY - 1];
	if (pDirection == direction::right) elementC = map[posX + 1][posY];
	if (pDirection == direction::down) elementC = map[posX][posY + 1];
	if (elementC == '#') collision = true;
	else collision = false;
}

void Player::addPoints() {
	score += 20 * scoreCombo;
	if (scoreCombo != 4) scoreCombo *= COMBO_BONUS;
}

void Player::enemyHit(int x, int y) {
	//TODO: Make it better!
	if (posX == x && posY == y) {
		health--;
		posX = DEFAULT_POSX;
		posY = DEFAULT_POSY;
	}

	if (health <= 0) {
		speed = 0;
		attron(COLOR_PAIR(4));
		mvprintw(DEFAULT_POSX - 5, DEFAULT_POSY, "GAME OVER!!");
	}
}

void Player::superpower() {

}

void Player::displayStats() {
	std::string healthText;
	for (int i = 1; i < health; i++) healthText += "o ";

	attron(COLOR_PAIR(3));
	mvprintw(3, 10, "PacMan");
	attron(COLOR_PAIR(1));
	mvprintw(4, 10, "Score:");
	mvprintw(4, 17, (std::to_string(score)).c_str());
	mvprintw(5, 10, "Health:");
	attron(COLOR_PAIR(4));
	mvprintw(5, 18, healthText.c_str());

	if (DEV_MODE == true) {
		attron(COLOR_PAIR(5));
		std::string devPlayer = "Player posX: " + std::to_string(posX) + " posY: " + std::to_string(posY);
		mvprintw(10, 10, devPlayer.c_str());	
		attron(COLOR_PAIR(6));
		if (collision) mvprintw(12, 10, "COLLISION!!!");
	}
	attron(COLOR_PAIR(1));
}