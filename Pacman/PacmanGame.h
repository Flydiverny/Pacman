#pragma once
#include "Map.h"
#include "Pacman.h"
#include <string>
#include "Player.h"
#include "Highscore.h"

namespace nadilus {
	namespace pacman {
		class PacmanGame {
			public:
				PacmanGame(void);
				~PacmanGame(void);

			private:
				Map map;
				Pacman pacman;
				Highscore highscore;
				Player player;
				int score;
				void printMap(void);
				void printTile(Tile t);
				void printPacman(void);
				void gotoxy(int x, int y);
				void playGame(void);
				Point getDirectionFromKeyboard(void);
				void changeDirection(Point p);
				void movePacman(void);
				void printScore(void);
				void printHighscore(void);
				void setScore(int s);
				void printMsg(std::string msg);
				void initialize(void);
				bool playAgain();
		};
	}
}
