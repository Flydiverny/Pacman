#pragma once
#include "Coord.h"

namespace SnakeGame {
	class Food
	{
		public:
			Food(Coord& coord) : _coord(coord) {}
			Food(int x, int y) : _coord(x,y) {}
			Coord& getCoord(void);

		private:
			Coord _coord;
			int weight;
	};
}
