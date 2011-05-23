#include "Map.h"
#include <fstream>
#include <Windows.h>
#include <vector>
#include "Point.h"
#include <iostream>

namespace nadilus {
	namespace pacman {
		Map::Map(std::string filename)
		{
			this->filename = filename;
			spawnSet = false;
			readMap();
		}

		Map::~Map(void) {}

		void Map::readMap(void) {
			std::ifstream data(filename);
			std::string line = "";
			spawnSet = false;
			std::vector<Tile*> list;
			std::vector<Ghost> ghostlist;
			if(data) {
				int row = 0;
				while ( data >> line ) {
					int length = line.length();
					this->columns = length;
					
					//Cstdlib way
					Tile* tileLine = (Tile*) malloc(length * sizeof(Tile));
					// new keyword way (doesnt work for tile since no default constructor
					//Tile* tileLine = new Tile[length];

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

						if(temp == '7') {
							Ghost g = Ghost();
							g.setPoint(Point(i,row));
							ghostlist.push_back(g);
						}

						tileLine[i] = Tile(atoi(&temp), temp != '1', p);
					}
					
					list.push_back(tileLine);
					row++;
				}

				this->tiles = (Tile**) malloc(list.size() * sizeof(Tile*));
				this->rows = list.size();

				//cstdlib C malloc way
				//this->ghosts = (Ghost*) malloc(ghostlist.size() * sizeof(Ghost));
				// new keyword c++ way
				this->ghosts = new Ghost[ghostlist.size()];
				this->ghostCount = ghostlist.size();

				for(unsigned i = 0; i < ghostlist.size(); i++) {
					this->ghosts[i] = ghostlist[i];
				}

				for(unsigned i = 0; i < list.size(); i++) {
					tiles[i] = list[i];
				}
			} else {
				std::cout << "Map file not found." << std::endl;
				system("PAUSE");
				exit(10);
			}
		}

		void Map::resetMap(void) {
			this->tiles = NULL;
			this->rows = 0;
			this->columns = 0;
		}

		unsigned Map::getRows(void) {
			return this->rows;
		}

		unsigned Map::getColumns(void) {
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

		Ghost*& Map::getGhosts(void) {
			return this->ghosts;
		}

		unsigned Map::getGhostCount(void) {
			return this->ghostCount;
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

		bool Map::hasFood(void) {
			for(unsigned r = 0; r < getRows(); r++) {
				for(unsigned c = 0; c < getColumns(); c++) {
					if(getTile(c,r).getType() == 0)
						return true;
				}
			}

			return false;
		}
	}
}