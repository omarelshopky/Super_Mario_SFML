#pragma once
#include <SFML/Graphics.hpp>
#include "../Header/DEFINITION.h"
#include <sstream>
#include<iomanip>
#include<fstream>
#include<map>

using namespace sf;
using namespace std;

class GameEngine
{
    /*          Properties          */
private:
    Font headerFont;
    ostringstream scoreStr, timerStr, coinsStr;
    Clock timer;
    int currentTime, levelTime, counterTime, scoreInt, fontSize, coinsInt;
    fstream playersFile;
    std::map<string, int> levelsMap;

public:
    Text timerText, scoreText, coinsText, levelText;
    RenderWindow *gameWindow;

    /*         Constractar          */
    GameEngine(RenderWindow& window);

    /*          Method         */
    
    // Update current score with Increased Score and display it
    void updateScore(int IncScore);


    // Start timer
    void startCountDown();


    // Update timer
    void updateTimer();


    // Check wheater Level time is finished or not
    bool isTimerFinished();
    

    // Convert remain time to score when player won
    void timeToScore();


    // draw GameEngine objects into screen
    void draw();


    // Increase coins counter by one
    void updateCoins();


    // Add player name , his score and level to Players file
    void addPlayerInfo(std::string playerName);


    // Sort players info according to score
    void sortPlayersFile();


    // Set level Name text
    void setLevelName(std::string levelName);
};

