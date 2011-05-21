#include "Map.h"
#include <fstream>
#include <Windows.h>
#include <vector>
#include "Point.h"
#include <iostream>

namespace nadilus {
	namespace pacman {
		Map::Map(void)
		{
			//initMap();
			spawnSet = false;
		}

		Map::~Map(void) {}

		void Map::initMap(void) {

		}

		void Map::readMap(std::string filename) {
			std::ifstream data(filename);
			std::string line = "";

			std::vector<Tile*> list;
			if(data) {
				int row = 0;
				while ( data >> line ) {
					int length = line.length();
					this->columns = length;
					Tile* tileLine = (Tile*) malloc(length * sizeof(Tile));

					for(int i = 0; i < length; i++) {
						char temp = line.at(i);
						Point p;
						p.x = i;
						p.y = row;
						
						if(temp == '9') {
							if(spawnSet) {
								std::cout << "Map may only have one spawn point please change the amount of '9'" << std::endl;
								system("PAUSE");
								exit(9);
							}

							this->spawnPoint = p;
							this->spawnSet = true;
						}

						tileLine[i] = Tile(atoi(&temp), temp != '1', p);
					}
					
					list.push_back(tileLine);
					row++;
				}

				this->tiles = (Tile**) malloc(list.size() * sizeof(Tile*));
				this->rows = list.size();

				for(int i = 0; i < list.size(); i++) {
					tiles[i] = list.at(i);
				}
			}
		}

		void Map::resetMap(void) {
		}

		int Map::getRows(void) {
			return this->rows;
		}

		int Map::getColumns(void) {
			return this->columns;
		}

		Tile**& Map::getTiles(void) {
			return this->tiles;
		}

		Tile& Map::getTile(int x, int y)  {
			return this->tiles[y][x];
		}

		Point Map::getSpawn(void) {
			return this->spawnPoint;
		}

		int Map::getColor(int type) {
			switch(type) {
				case 0:
					return 252;
				case 1:
					return 248;
				case 2:
					return 255;
				default:
					return -1;
			}
		}
	}
}