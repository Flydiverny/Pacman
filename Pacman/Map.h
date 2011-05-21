#pragma once
#include "Tile.h"
#include <string>

namespace nadilus {
	namespace pacman {
		class Map {
			public:
				Map(void);
				~Map(void);
				void	resetMap(void);
				int		getRows(void);
				int		getColumns(void);
				Point	getSpawn(void);
				void	readMap(std::string);
				int		getColor(int type);
				Tile**&	getTiles(void);
				Tile&	getTile(int x, int y);
				bool	hasFood(void);
				Point	getDrawPoint(void);
				void	setDrawPoint(Point p);

			private:
				int		rows;
				int		columns;
				Point	spawnPoint;
				bool	spawnSet;
				void	initMap(void);
				Point	drawPoint;
				
				Tile**	tiles;
		};
	}
}
