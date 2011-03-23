#pragma once
namespace SnakeGame {
	class Coord
	{
		public:
			Coord(int x, int y) : x(x), y(y) {}
			explicit Coord(const Coord& coord) : x(coord.x), y(coord.y) {}

			int getX();
			int getY();
		private:
			int x;
			int y;
	};
}
