//Pacman by Wojciech redacted
//2018

#include "pch.h"
#include <stdio.h>
#include <conio.h>
#include <curses.h>
#include <windows.h>

#include "Level.h"
#include "Player.h"
#include "Ghost.h"
#include "Menu.h"

const short DELAY = 250; //Prędkość działania gry

char c; //Zmienna przechowywująca wcisnkane klawisze

char ** map;

int room = 2;

Level level;
Menu menu;
Player player;
Ghost ghost, ghostTwo, ghostThree, ghostFour;

direction control(char ch) {

	switch (ch) {
	case 'a':
		return left;
		break;
	case 'w':
		return up;
		break;
	case 'd':
		return right;
		break;
	case 's':
		return down;
		break;
	case 'c':
		return confirm;
		break;
	}
	return none;
}

void init() {
	//Funkcja inicjująca wszystkie funkcje niezbędne do działania gry
	initscr(); //Uruchomienie biblioteki ncurses
	noecho(); //Ukrycie wciskiwanych przycisków prez użytkownika
	curs_set(false); //Ukrycie kursora
	nodelay(stdscr, true); //Gra nie będzie czekała na wciśnięcie przycisku przez gracza
	start_color(); //Aktywowanie trybu kolorów
	init_pair(1, COLOR_WHITE, COLOR_BLACK);//Ustawienie zestawów kolorów
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLUE);
	init_pair(6, COLOR_WHITE, COLOR_RED);

	level.buildLevel(); //Wczytanie i wygenerowanie poziomu
	map = level.getMap();
}

void update() {
	//Funkcja odpowiadająca za odświeżanie gry
	c = getch();
	int currentElement = 0;
	int menuChoice;

	clear(); //Wyczyszczenie ekranu po poprzedniej 'klatce'

	if (room == 1) {
		menuChoice = menu.control(control(c));
		if (menuChoice == 1) room = 2;
		//if (menuChoice == 2) room = 3;
		if (menuChoice == 3) std::exit(0);
	}

	if (room == 2) {
		Sleep(DELAY); //'Zatrzymanie' gry w ms. W zasadzie reguluje prędkość gry
		player.setPlayerDirection(control(c)); //Sterowanie
		player.movePlayer(map); //Przemieszcza gracza o jedno pole
		player.checkElement(map); //Sprawdza na jakim polu znajduje się gracz

		ghost.moveEnemy(map); //Przemieszcza duszka o jedno pole
		ghostTwo.moveEnemy(map);
		ghostThree.moveEnemy(map);
		ghostFour.moveEnemy(map);

		player.enemyHit(ghost.getEnemyPosX(), ghost.getEnemyPosY());
		player.enemyHit(ghostTwo.getEnemyPosX(), ghostTwo.getEnemyPosY());
		player.enemyHit(ghostThree.getEnemyPosX(), ghostThree.getEnemyPosY());
		player.enemyHit(ghostFour.getEnemyPosX(), ghostFour.getEnemyPosY());
		//level.deleteMap(map); //Zwalnia miejsce w pamięci zajmowaną przez mape
	}
}

void display() {
	//Funkcja odpowiadająca za wyświetlenie gry
	if (room == 1) {
		menu.displayMenu();
	}

	if (room == 2) {
		level.displayLevel(map); //Wyświetlenie poziomu

		player.displayStats(); //Wyświetla statystyki
		player.displayPlayer(); //Wyświetla gracza

		ghost.displayEnemy(); //Wyświetla duszki
		ghostTwo.displayEnemy();
		ghostThree.displayEnemy();
		ghostFour.displayEnemy();
	}
	refresh(); //Wyświetla wszystkie elementy
}


int main() {
	//Nic ciekawego, po prostu pętla gry :)
	init();
	while (true) {
		update();
		display();
	}
}