#pragma once
#include "Coord.h"
#include <vector>

namespace SnakeGame {
	class Snake {
		public:
			Snake(Coord head) : head(head) {}
			~Snake(void);

		private:
			Coord head;
			std::vector<Coord> body;
	};
}