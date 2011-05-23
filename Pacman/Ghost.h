#pragma once
#include "Creature.h"

namespace nadilus {
	namespace pacman {
		class Ghost : public Creature {
			public:
				Ghost(void) : Creature() { this->setDirection(1,0); }
				~Ghost(void);
			private:
		};
	}
}

