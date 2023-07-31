#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace neko {
	class Highscore {
	public:

		Highscore();
		int readHighScore();
		void saveHighScore(int score);
	};
}