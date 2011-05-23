#include "Creature.h"

namespace nadilus {
	namespace pacman {
		Creature::Creature(void)
		{
			this->point.x = 0;
			this->point.y = 0;
			this->dx = 0;
			this->dy = 0;
		}


		Creature::~Creature(void)
		{
		}

		Point& Creature::getPoint(void) {
			return this->point;
		}

		Point Creature::getNextPoint(void) {
			return Point(this->point.x+dx, this->point.y+dy);
		}

		bool Creature::isMoving(void) {
			Point p = this->getPoint();
			Point n = this->getNextPoint();
			return !(p.x == n.x && p.y == n.y);
		}

		void Creature::setPoint(Point p) {
			this->point = p;
		}

		void Creature::setDirection(int dx, int dy) {
			if(dx <= 1 && dx >= -1) {
				this->dx = dx;
			}
			if(dy <= 1 && dy >= -1) {
				this->dy = dy;
			}
		}

		Point Creature::getDirection(void) {
			return Point(this->dx, this->dy);
		}

		Point Creature::getLastPoint(void) {
			return this->lastPoint;
		}

		void Creature::move(void) {
			this->lastPoint = point;
			this->point = this->getNextPoint();
		}
	}
}