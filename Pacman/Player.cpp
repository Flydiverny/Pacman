#include "Player.h"
#include "Util.cpp"

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
			findAndReplace<std::string>(name," ", "_");
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