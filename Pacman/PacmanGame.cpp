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
			this->map = Map("map.txt");
			this->highscore = Highscore("score.txt");
			this->drawPoint = Point(3,2);
			
			initialize();
		}

		PacmanGame::~PacmanGame(void) {
		}
	
		void PacmanGame::initialize(void) {
			printHighscore(-1);
			printScore();

			printMsg("Welcome to Pacman!");
			Sleep(200);
			printMsg("Please enter your name: ");

			char playerName[8];
			cin.get(playerName, 9);

			player.setName(playerName);

			do {
				score = 0;
				printMsg("Dat pacman map coming up!");
				printMap();
				printMsg("Good Luck " + player.getName() +"!");
				playGame();
				highscore.saveHighscore();
				this->map = Map("map.txt");
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
			for(unsigned i = 0; i < map.getRows(); i++) {
				for(unsigned x = 0; x < map.getColumns(); x++) {
					printTile(map.getTile(x,i));
					//Sleep(7);
				}
				Sleep(20);
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
			Point p = this->pacman.getPoint();
			gotoxy(p.x,p.y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
			cout << (char) 2;
		}

		void PacmanGame::printGhosts(void) {
			Ghost* ghosts = map.getGhosts();
			unsigned gcount = map.getGhostCount();
			
			for(unsigned i = 0; i < gcount; i++) {
				Point p = ghosts[i].getPoint();
				gotoxy(p.x,p.y);
				int color = 251 + i < 256 ?  251 + i  : 251;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
				cout << (char) 2;
			}
		}

		void PacmanGame::printMsg(string msg) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

			for(unsigned i = 0; i < map.getColumns(); i++) {
				gotoxy(0+i,map.getRows());
				cout << " ";
			}

			for(unsigned i = 0; i < msg.length(); i++) {
				gotoxy(0+i,map.getRows());
				cout << msg.at(i);

				Sleep(45);
			}
		}

		void PacmanGame::playGame(void) {
			int moveLoops = 4;
			int currentLoop = 0;

			initGhostMovements();

			while(true) {
				if(!map.hasFood()) break;
				Sleep(50);

				if(_kbhit()) changeDirection(getDirectionFromKeyboard());
				
				if(currentLoop < moveLoops) currentLoop++;
				else {
					movePacman();
					moveGhosts();
					currentLoop = 0;
				}
				
				setScore(-1);

				printScore();
				if(!map.hasFood()) break;
			}

			//Could uncomment if we want to save the highestscore only for player
			//but currently theres no real point with that
			//if(score >= player.getHighscore()) {
				player.setHighscore(score);
				int position = highscore.addPlayer(player);
			//}

			printHighscore(position);
		}

		void PacmanGame::setScore(int s) {
			this->score += s;
			if(score < 0) score = 0;
		}

		void PacmanGame::printHighscore(int position) {
			gotoxy(map.getColumns()+3,-1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "Highscore List ";
			string splitter = "-----------------------";
			gotoxy(map.getColumns()+3,0);
			cout << splitter;
			
			deque<Player> list = this->highscore.getList();

			for(unsigned i = 0; i < map.getRows()-2; i++) {
				if(list.size() < i+1) break;

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				if(i == position) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				
				gotoxy(map.getColumns()+3,1+i);
				cout << "                       ";
				gotoxy(map.getColumns()+3,1+i);

				if(i < 9) cout << " ";
				cout << i+1 << " " << list.at(i).getName();

				coutScore(list.at(i).getHighscore(), map.getColumns()+2+splitter.length(), 1+i);
			}

			gotoxy(map.getColumns()+3,map.getRows()-1);
			cout << splitter;

			if(position > -1) {
				if(list.size() > map.getRows()-3 && player.getHighscore() <= list.at(map.getRows()-3).getHighscore()) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
					gotoxy(map.getColumns()+3,map.getRows());
					cout << position << " " << player.getName();

					coutScore(player.getHighscore(), map.getColumns()+2+splitter.length(), map.getRows());
				}
			}
		}

		void PacmanGame::coutScore(int score, int x, int y) {
			if(score < 10) gotoxy(x,y);
			else if(score < 100) gotoxy(x-1,y);
			else if(score < 1000) gotoxy(x-2,y);
			else if(score < 10000) gotoxy(x-3,y);
			else if(score < 100000) gotoxy(x-4,y);
			cout << score;
		}

		void PacmanGame::printScore(void) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			gotoxy(0,-1);
			cout << "Score:";

			gotoxy(map.getColumns()-7,-1);
			cout << "       ";

			coutScore(score, map.getColumns()-1, -1);
		}

		void PacmanGame::movePacman(void) {
			Point np = pacman.getNextPoint();
			if(!map.getTile(np.x,np.y).isWalkable()) return;

			Point pmp = pacman.getPoint();

			if(map.getTile(np.x,np.y).getType() == 0) setScore(50);
			else if(pacman.isMoving()) setScore(-10);

			
			Tile& t = map.getTile(pmp.x,pmp.y);
			Tile& t2 = map.getTile(np.x,np.y);
			
			t.setType(2);
			t2.setType(2);
			printTile(t);

			pacman.move();
			printPacman();
		}

		void PacmanGame::initGhostMovements(void) {
			Ghost* ghosts = map.getGhosts();
			unsigned gcount = map.getGhostCount();

			for(unsigned i = 0; i < gcount; i++) {
				ghosts[i].setDirection(1, 0);
				Point np = ghosts[i].getNextPoint();

				int x=0;
				while(!map.getTile(np.x,np.y).isWalkable() && x < 4) {
					switch(x) {
						case 0:
							ghosts[i].setDirection(1, 0);
							break;
						case 1:
							ghosts[i].setDirection(0, -1);
							break;
						case 2:
							ghosts[i].setDirection(0, 1);
							break;
						case 3:
							ghosts[i].setDirection(-1, 0);
							break;
					}
					x++;
					np = ghosts[i].getNextPoint();
				}
			}
		}

		void PacmanGame::moveGhosts(void) {
			Ghost* ghosts = map.getGhosts();
			unsigned gcount = map.getGhostCount();

			for(unsigned i = 0; i < gcount; i++) {
				Point np = ghosts[i].getNextPoint();

				Point pmd = pacman.getDirection();
				int x=0;
				while((!map.getTile(np.x,np.y).isWalkable()) && x < 4) {
					switch(x) {
						case 0:
							ghosts[i].setDirection(1, 0);
							break;
						case 1:
							ghosts[i].setDirection(0, -1);
							break;
						case 2:
							ghosts[i].setDirection(0, 1);
							break;
						case 3:
							ghosts[i].setDirection(-1, 0);
							break;
					}
					x++;
					np = ghosts[i].getNextPoint();
				}

				Point pmp = ghosts[i].getPoint();

				Tile& t = map.getTile(pmp.x,pmp.y);
				printTile(t);

				ghosts[i].move();
			}

			//Tile& t2 = map.getTile(np.x,np.y);
			//t2.setType(2);

			printGhosts();
		}


		Point PacmanGame::getDirectionFromKeyboard(void) {
			switch(_getch()){
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
			Point mp = drawPoint;
			coord.X = x+mp.x;
			coord.Y = y+mp.y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}
	}
}
