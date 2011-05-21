#include "Pacman.h"

namespace nadilus {
	namespace pacman {
		Pacman::Pacman(void)
		{
			this->point.x = 0;
			this->point.y = 0;
			this->dx = 0;
			this->dy = 0;
		}


		Pacman::~Pacman(void)
		{
		}

		Point& Pacman::getPoint(void) {
			return this->point;
		}

		void Pacman::setPoint(Point p) {
			this->point = p;
		}

		void Pacman::setDirection(int dx, int dy) {
			if(dx <= 1 && dx >= -1) {
				this->dx = dx;
			}
			if(dy <= 1 && dy >= -1) {
				this->dy = dy;
			}
		}
	}
}