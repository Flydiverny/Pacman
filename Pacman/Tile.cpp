#include "Tile.h"

namespace nadilus {
	namespace pacman {
		Tile::Tile(int type, bool walkable, Point p) {
			this->type = type;
			this->walkable = walkable;
			this->point = p;
		}

		Tile::~Tile(void)
		{
		}

		bool Tile::isWalkable(void) {
			return this->walkable;
		}

		void Tile::setType(int type) {
			this->type = type;
		}

		int Tile::getType(void) {
			return this->type;
		}

		char Tile::toChar() {
			switch(this->getType()) {
				case 0:
					return (char)3;
				case 1:
					return (char)219;
				case 2:
					return (char)0;
				default:
					return (char)0;
			}
		}
	}
}
