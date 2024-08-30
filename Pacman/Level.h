#pragma once

#include <iostream>
#include <string>
#include <vector>

class Level {
private:
	void loadLevel();
	char map[28][27];
public:
	void buildLevel();
	void displayLevel(char ** tmpMap);
	char ** getMap();
	void deleteMap(char ** tmpMap);
};