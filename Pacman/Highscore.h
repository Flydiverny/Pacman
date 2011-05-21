#pragma once
#include "Player.h"
#include <deque>

namespace nadilus {
	namespace pacman {
		class Highscore	{
			public:
				Highscore(void) {}
				Highscore(std::string filename);
				~Highscore(void);

				std::deque<Player>	getList(void);
				int					addPlayer(Player);
				void				readHighscore();
				void				saveHighscore();

			private:
				std::deque<Player> list;
				std::string filename;
		};
	}
}
