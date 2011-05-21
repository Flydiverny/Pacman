#pragma once
#include "Player.h"
#include <deque>

namespace nadilus {
	namespace pacman {
		class Highscore	{
			public:
				Highscore(void);
				~Highscore(void);

				std::deque<Player>	getList(void);
				void				addPlayer(Player);
				void				readHighscore(std::string filename);

			private:
				std::deque<Player> highscorelist;
		};
	}
}
