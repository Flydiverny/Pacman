#pragma once
#include <string>
#include "Point.h"

namespace nadilus {
	namespace pacman {
		class Tile {
			public:
				Tile(int type, bool walkable, Point p);
				~Tile(void);
				bool isWalkable(void);
				int getType(void);
				void setType(int type);
				char toChar();

			private:
				Point point;
				int type;
				bool walkable; 
		};
	}
}
