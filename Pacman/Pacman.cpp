#include "Pacman.h"

namespace nadilus {
	namespace pacman {
		Pacman::~Pacman(void)
		{
		}

		bool Pacman::isAlive(void) {
			return this->alive;
		}

		void Pacman::setAlive(bool alive) {
			this->alive = alive;
		}
	}
}