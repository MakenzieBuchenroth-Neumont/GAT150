#include "HighScore.h"
#include <fstream>
#include <iostream>

namespace neko {
    Highscore::Highscore() {}

    int Highscore::readHighScore() {
        int highScore = 0;
        std::ifstream file("highscore.txt");
        if (file.is_open()) {
            file >> highScore;
            file.close();
        }
        else {
            std::cout << "Unable to read high score! Using default value 0." << std::endl;
        }
        return highScore;
    }

    void Highscore::saveHighScore(int score) {
        std::ofstream file("highscore.txt");
        if (file.is_open()) {
            file << score;
            file.close();
            std::cout << "High score saved successfully!" << std::endl;
        }
        else {
            std::cout << "Unable to save high score!" << std::endl;
        }
    }
}