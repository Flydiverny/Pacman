#pragma once
#include <string>

namespace nadilus {
	namespace pacman {
		class Player
		{
			public:
				Player(void);
				~Player(void);

				void		setName(std::string);
				void		setHighscore(int);
				int			getHighscore(void);
				std::string	getName(void);

			private:
				std::string name;
				int highscore;
		};
	}
}
