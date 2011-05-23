#include "Point.h"

namespace nadilus {
	namespace pacman {
		Point::Point(void) {
			this->x = 0;
			this->y = 0;
		}

		Point::~Point(void)
		{
		}

		bool operator==(Point p1, Point p2) {
			return (p1.x == p2.x && p1.y == p2.y);
		}

		bool operator!=(Point p1, Point p2) {
			return !(p1 == p2);
		}
	}
}