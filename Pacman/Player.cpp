#include "Player.h"

namespace nadilus {
	namespace pacman {
		Player::Player(void) {
			this->name = "";
			this->highscore = 0;
		}


		Player::~Player(void)
		{
		}

		void Player::setName(std::string name) {
			this->name = name;
		}

		std::string Player::getName(void) {
			return this->name;
		}

		int Player::getHighscore(void) {
			return this->highscore;
		}

		void Player::setHighscore(int score) {
			this->highscore = score;
		}
	}
}