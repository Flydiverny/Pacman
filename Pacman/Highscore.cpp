#include "Highscore.h"
#include <fstream>

namespace nadilus {
	namespace pacman {
		Highscore::Highscore(std::string filename) {
			this->list = std::deque<Player>();
			this->filename = filename;
			this->readHighscore();
		}

		Highscore::~Highscore(void)	{}

		void Highscore::readHighscore(void) {
			std::ifstream data(filename);
			std::string line = "";
			std::string score = "";
			if(data) {
				int row = 0;
				while ( data >> line && data >> score) {
					Player p = Player();
					p.setName(line);
					p.setHighscore(atoi(score.c_str()));
					this->list.push_back(p);
				}
			}
		}

		void Highscore::saveHighscore(void) {
			std::ofstream data(filename);
			for each(Player p in list) {
				data << p.getName() << " " << p.getHighscore() << std::endl;
			}
		}

		std::deque<Player> Highscore::getList(void) {
			return this->list;
		}

		int Highscore::addPlayer(Player p) {
			for(unsigned i = 0; i < list.size(); i++) {
				Player ph = list.at(i);
				if(ph.getHighscore() < p.getHighscore()) {
					list.insert(list.begin()+i,p);
					return i;
				}
			}

			if(list.size() < 99)
				list.push_back(p);

			return list.size();
		}
	}
}
