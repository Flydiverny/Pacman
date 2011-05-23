#include "Ghost.h"

namespace nadilus {
	namespace pacman {
		Ghost::~Ghost(void)
		{
		}

		Point* Ghost::getPaths(void) {
			Point* pts = new Point[4];
			Point p = this->getPoint();

			pts[0].x = p.x + 1;
			pts[0].y = p.y;

			pts[1].x = p.x - 1;
			pts[1].y = p.y;

			pts[2].x = p.x;
			pts[2].y = p.y + 1;

			pts[3].x = p.x;
			pts[3].y = p.y - 1;

			return pts;
		}
	}
}