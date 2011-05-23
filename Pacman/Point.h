#pragma once
namespace nadilus {
	namespace pacman {
		class Point {
			public:
				Point(void);
				Point(int x, int y) : x(x), y(y) {}
				~Point(void);
				int x;
				int y;

				friend bool operator==(Point,Point);
				friend bool operator!=(Point,Point);
		};
	}
}