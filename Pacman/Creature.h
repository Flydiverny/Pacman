#pragma once
#include "Point.h"

namespace nadilus {
	namespace pacman {
		class Creature {
			public:
				Creature(void);
				~Creature(void);

				void	setDirection(int dx, int dy);

				Point&	getPoint();
				Point	getNextPoint();
				void	setPoint(Point p);
				void	move(void);
				bool	isMoving(void);
			private:
				Point	point;
				short	dx,dy;
		};
	}
}
