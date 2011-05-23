#pragma once
#include "Creature.h"

namespace nadilus {
	namespace pacman {
		class Pacman : public Creature {
			public:
				Pacman(void) : Creature(), alive(true) {}
				~Pacman(void);

				bool isAlive(void);
				void setAlive(bool);
			private:
				bool alive;
		};
	}
}
