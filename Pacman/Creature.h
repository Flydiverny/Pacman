#pragma once
#include "Point.h"

namespace nadilus {
	namespace pacman {
		class Creature {
			public:
				Creature(void);
				~Creature(void);

				void	setDirection(int dx, int dy);
				Point	getDirection(void);

				Point&	getPoint();
				Point	getNextPoint();
				Point	getLastPoint();
				void	setPoint(Point p);
				void	move(void);
				bool	isMoving(void);

			private:
				Point	point;
				Point	lastPoint;
				short	dx,dy;
		};
	}
}
