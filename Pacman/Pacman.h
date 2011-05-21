#pragma once
#include "Point.h"

namespace nadilus {
	namespace pacman {
		class Pacman {
			public:
				Pacman(void);
				~Pacman(void);

				void setDirection(int dx, int dy);

				Point& getPoint();
				void setPoint(Point p);
			private:
				Point point;
				short dx,dy;
		};
	}
}
