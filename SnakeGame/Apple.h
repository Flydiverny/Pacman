#pragma once
#include "Coord.h"
#include "Food.h"

namespace SnakeGame {
	class Apple : public Food {


		public:
			Apple(Coord& coord) : Food(coord) {}
			Apple(int x, int y) : Food(x,y) {}
			~Apple(void);
	};
}
