#pragma once
#include <string>

namespace SnakeGame {
	class Map 	{
		public:
			Map(void);
			~Map(void);

		private:
			std::string** mapArray;
	};
}