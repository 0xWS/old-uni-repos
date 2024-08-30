#pragma once

class Menu {
private:
	bool room;
	int menuPos = 1;
public:
	void displayMenu();
	int control(int ch);
};