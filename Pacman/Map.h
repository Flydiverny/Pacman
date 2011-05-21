#pragma once
#include "Tile.h"
#include <string>

namespace nadilus {
	namespace pacman {
		class Map {
			public:
				Map(void) {}
				Map(std::string);
				~Map(void);
				void	resetMap(void);
				unsigned getRows(void);
				unsigned getColumns(void);
				Point	getSpawn(void);
				void	readMap();
				int		getColor(int type);
				Tile**&	getTiles(void);
				Tile&	getTile(int x, int y);
				bool	hasFood(void);
				Point	getDrawPoint(void);
				void	setDrawPoint(Point p);

			private:
				unsigned rows;
				unsigned columns;
				Point	spawnPoint;
				bool	spawnSet;
				void	initMap(void);
				Point	drawPoint;
				std::string filename;
				Tile**	tiles;
		};
	}
}
