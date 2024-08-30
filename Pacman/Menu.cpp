#include "Menu.h"
#include <curses.h>

void Menu::displayMenu() {
	attron(COLOR_PAIR(3));
	mvprintw(5, 32, "___________    ____   _____ _____    ____");
	mvprintw(6, 32, "\\____ \\__  \\ _/ ___\\ /     \\\\__  \\  /    \\");
	mvprintw(7, 32, "|  |_> > __ \\\\  \\___|  Y Y  \\/ __ \\|   |  \\ ");
	mvprintw(8, 32, "|   __(____  /\\___  >__|_|  (____  /___|  /");
	mvprintw(9, 32, "|__|       \\/     \\/     \\/     \\/     \\/");
	attron(COLOR_PAIR(1));
	//mvprintw(7, 32, "by Kitsu");
	mvprintw(16, 50, "Start");
	//mvprintw(17, 50, "About");
	//mvprintw(18, 50, "Exit");
	if (menuPos == 1) mvprintw(16, 47, ">>");
	if (menuPos == 2) mvprintw(17, 47, ">>");
	if (menuPos == 3) mvprintw(18, 47, ">>");
}

int Menu::control(int ch) {
	/*if (ch == 2) {
		if (menuPos != 1) menuPos--;
		else menuPos = 3;
	}
	if (ch == 4) {
		if (menuPos != 3) menuPos++;
		else menuPos = 1;
	}*/
	if (ch == 6) {
		//return menuPos;
		return 1;
	}
	return 0;
}