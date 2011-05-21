#include "PacmanGame.h"
#include "Tile.h"
#include <iostream>
#include <windows.h>
#include "Point.h"
#include <conio.h>

using namespace std;

namespace nadilus {
	namespace pacman {
		PacmanGame::PacmanGame(void) {
			score = 0;
			map.readMap("map.txt");
			map.setDrawPoint(Point(3,2));

			//highscore.readHighscore("highscore.txt");
			
			initialize();
		}

		PacmanGame::~PacmanGame(void) {
		}
	
		void PacmanGame::initialize(void) {
			printHighscore();
			printScore();

			printMsg("Welcome to Pacman!");
			Sleep(200);
			printMsg("Please enter your name: ");

			string playerName;

			cin >> playerName;

			player.setName(playerName);

			do {
				score = 0;
				printMsg("Dat pacman map coming up!");
				printMap();
				printMsg("Good Luck " + player.getName() +"!");
				playGame();
				map.readMap("map.txt");
			} while(playAgain());

			printMsg("Good Bye " + player.getName() + " it was fun playing with you!");
			Sleep(500);
		}

		bool PacmanGame::playAgain() {
			while(true) {
				printMsg("Do you want to play again? [Y/N]: ");

				string input;
				cin >> input;

				if(input == "Y" || input == "y")
					return true;
				
				if(input == "N" || input == "n")
					return false;
			}
		}

		void PacmanGame::printMap(void) {
			for(int i = 0; i < map.getRows(); i++) {
				for(int x = 0; x < map.getColumns(); x++) {
					printTile(map.getTile(x,i));
					Sleep(7);
				}
			}

			Point spawn = map.getSpawn();

			// New map drawn so make a new pacman to reset dx, dy etc.
			this->pacman = Pacman();
			pacman.setPoint(spawn);
		}

		void PacmanGame::printTile(Tile t) {
			Point p = t.getPoint();
			gotoxy(p.x,p.y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), map.getColor(t.getType()));
			cout << t.toChar();
		}

		void PacmanGame::printPacman(void) {
			Point mp = map.getDrawPoint();
			Point p = this->pacman.getPoint();
			gotoxy(p.x,p.y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
			cout << (char) 2;
		}

		void PacmanGame::printMsg(string msg) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

			for(int i = 0; i < map.getColumns(); i++) {
				gotoxy(0+i,map.getRows());
				cout << " ";
			}

			for(int i = 0; i < msg.length(); i++) {
				gotoxy(0+i,map.getRows());
				cout << msg.at(i);

				Sleep(55);
			}
		}

		void PacmanGame::playGame(void) {
			int moveLoops = 4;
			int currentLoop = 0;

			while(map.hasFood()) {
				Sleep(50);

				if(kbhit()) changeDirection(getDirectionFromKeyboard());
				
				if(currentLoop < moveLoops) currentLoop++;
				else {
					movePacman();
					currentLoop = 0;
				}
				
				setScore(-1);

				printScore();
			}

			if(score > player.getHighscore()) {
				player.setHighscore(score);
				highscore.addPlayer(player);
			}

			printHighscore();
		}

		void PacmanGame::setScore(int s) {
			this->score += s;
			if(score < 0) score = 0;
		}

		void PacmanGame::printHighscore(void) {
			gotoxy(map.getColumns()+3,-1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "Highscore List ";
			string splitter = "-----------------------";
			gotoxy(map.getColumns()+3,0);
			cout << splitter;
			
			deque<Player> list = this->highscore.getList();

			for(int i = 0; i < map.getRows()-2; i++) {
				if(list.size() < i+1) break;
				gotoxy(map.getColumns()+3,1+i);
				cout << "                       ";
				gotoxy(map.getColumns()+3,1+i);

				if(i < 9) cout << " ";
				cout << i+1 << " " << list.at(i).getName();

				int score = list.at(i).getHighscore();
				if(score < 10) gotoxy(map.getColumns()+2+splitter.length(),1+i);
				else if(score < 100) gotoxy(map.getColumns()+2+splitter.length()-1,1+i);
				else if(score < 1000) gotoxy(map.getColumns()+2+splitter.length()-2,1+i);
				else if(score < 10000) gotoxy(map.getColumns()+2+splitter.length()-3,1+i);
				else if(score < 100000) gotoxy(map.getColumns()+2+splitter.length()-4,1+i);
				cout << score;
			}

			gotoxy(map.getColumns()+3,map.getRows()-1);
			cout << splitter;

			if(list.size() > map.getRows()-3 && player.getHighscore() <= list.at(map.getRows()-3).getHighscore()) {
				gotoxy(map.getColumns()+3,map.getRows());
				cout << "-- " << player.getName();

				int score = player.getHighscore();
				if(score < 10) gotoxy(map.getColumns()+2+splitter.length(),map.getRows());
				else if(score < 100) gotoxy(map.getColumns()+2+splitter.length()-1,map.getRows());
				else if(score < 1000) gotoxy(map.getColumns()+2+splitter.length()-2,map.getRows());
				else if(score < 10000) gotoxy(map.getColumns()+2+splitter.length()-3,map.getRows());
				else if(score < 100000) gotoxy(map.getColumns()+2+splitter.length()-4,map.getRows());
				cout << score;
			}
		}

		void PacmanGame::printScore(void) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			gotoxy(0,-1);
			cout << "Score:";

			gotoxy(map.getColumns()-7,-1);
			cout << "       ";

			if(score < 10) gotoxy(map.getColumns()-1,-1);
			else if(score < 100) gotoxy(map.getColumns()-2,-1);
			else if(score < 1000) gotoxy(map.getColumns()-3,-1);
			else if(score < 10000) gotoxy(map.getColumns()-4,-1);
			else if(score < 100000) gotoxy(map.getColumns()-5,-1);
			cout << score;
		}

		void PacmanGame::movePacman(void) {
			Point np = pacman.getNextPoint();
			if(!map.getTile(np.x,np.y).isWalkable()) return;

			Point pmp = pacman.getPoint();

			Tile& t = map.getTile(pmp.x,pmp.y);
			
			t.setType(2);
			printTile(t);

			if(map.getTile(np.x,np.y).getType() == 0) setScore(50);
			else if(pacman.isMoving()) setScore(-10);

			pacman.move();
			printPacman();
		}

		Point PacmanGame::getDirectionFromKeyboard(void) {
			switch(getch()){
				case 77:
					return Point(1, 0);
				case 75:
					return Point(-1, 0);
				case 72:
					return Point(0, -1);
				case 80:
					return Point(0, 1);
				default:
					return Point();
			}
			
		}

		void PacmanGame::changeDirection(Point p) {
			if(p.x == 0 && p.y == 0) return;

			if(map.getTile(pacman.getPoint().x+p.x,pacman.getPoint().y+p.y).isWalkable()) {
				pacman.setDirection(p.x,p.y);
			}
		}

		void PacmanGame::gotoxy(int x, int y) {
			COORD coord;
			Point mp = map.getDrawPoint();
			coord.X = x+mp.x;
			coord.Y = y+mp.y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}
	}
}
