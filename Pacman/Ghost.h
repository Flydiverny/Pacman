#pragma once
#include "Creature.h"

namespace nadilus {
	namespace pacman {
		class Ghost : public Creature {
			public:
				Ghost(void) : Creature() {}
				~Ghost(void);
			private:
		};
	}
}

