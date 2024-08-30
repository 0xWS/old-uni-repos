#include "Level.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <curses.h>

void Level::loadLevel() {
	std::ifstream level("level.lvl"); //Wczytanie pliku poziomu
	if (!level) { //Wyrzucenie b³êdu je¿eli nie mo¿na go wczytaæ
		std::cerr << "Cannot open level file." << std::endl;
	}
	else {
		//Wczytanie poziomu do macierzy
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 28; j++) {
				level >> std::noskipws >> map[j][i];
			}
		}
	}
 	level.close();
}

void Level::buildLevel() {
	//TODO: Dodatkowe funkcje po wczytaniu poziomu?
	loadLevel();
}

void Level::displayLevel(char ** tmpMap) {
	//Funkcja ta wyœwietla poziom
	char element;
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 27; j++) {
			element = tmpMap[j][i];
			if(element == '#') attron(COLOR_PAIR(2));
			if (element == '$' || element == '*') attron(COLOR_PAIR(3));
			mvaddch(i, j+35, element);
		}
	}
	attron(COLOR_PAIR(1));
}

char ** Level::getMap() {
	char ** tmpMap = new char * [28];
	for (int i = 0; i < 28; i++) {
		tmpMap[i] = new char[27];
		for (int j = 0; j < 27; j++) {
			tmpMap[i][j] = map[i][j];
		}
	}
	return tmpMap;
}

void Level::deleteMap(char ** tmpMap) {
	delete [] tmpMap;
}