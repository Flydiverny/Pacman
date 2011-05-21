#include "Highscore.h"

namespace nadilus {
	namespace pacman {
		Highscore::Highscore(void) {
			this->highscorelist = std::deque<Player>();
		}


		Highscore::~Highscore(void)
		{
		}

		std::deque<Player> Highscore::getList(void) {
			return this->highscorelist;
		}

		void Highscore::addPlayer(Player p) {

			for(int i = 0; i < highscorelist.size(); i++) {
				Player ph = highscorelist.at(i);
				if(ph.getHighscore() < p.getHighscore()) {
					highscorelist.insert(highscorelist.begin()+i,p);
					return;
				}
			}

			highscorelist.push_back(p);
		}
	}
}
