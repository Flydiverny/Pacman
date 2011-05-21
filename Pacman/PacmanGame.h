#pragma once
#include "Map.h"
#include "Pacman.h"

namespace nadilus {
	namespace pacman {
		class PacmanGame {
			public:
				PacmanGame(void);
				~PacmanGame(void);

			private:
				Map map;
				Pacman pacman;
				int score;
				void printMap(void);
				void printTile(Point p);
				void printPacman(void);
				void gotoxy(int x, int y);
				void playGame(void);
		};
	}
}