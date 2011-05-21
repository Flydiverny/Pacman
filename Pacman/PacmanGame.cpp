#include "PacmanGame.h"
#include <string>
#include "Tile.h"
#include <iostream>
#include <windows.h>
#include "Point.h"

using namespace std;

namespace nadilus {
	namespace pacman {
		PacmanGame::PacmanGame(void) {
			map.readMap("map.txt");
			printMap();
			playGame();
		}

		PacmanGame::~PacmanGame(void) {
		}

		void PacmanGame::printMap(void) {
			gotoxy(0,0);
			for(int i = 0; i < map.getRows(); i++) {
				for(int x = 0; x < map.getColumns(); x++) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), map.getColor(map.getTiles()[i][x].getType()));
					cout << map.getTiles()[i][x].toChar();
				}
				cout << endl;
			}

			pacman.setPoint(map.getSpawn());
		}

		void PacmanGame::printTile(Point p) {
			gotoxy(p.x,p.y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), map.getColor(map.getTile(p.x,p.y).getType()));
			cout << map.getTile(p.x,p.y).toChar();
		}

		void PacmanGame::printPacman(void) {
			Point p = this->pacman.getPoint();
			gotoxy(p.x,p.y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
			cout << (char) 2;
		}

		void PacmanGame::playGame(void) {
			while(true) {

				
				printPacman();
				Sleep(300);
			}
		}

		void PacmanGame::gotoxy(int x, int y) {
			COORD coord;
			coord.X = x;
			coord.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}
	}
}
