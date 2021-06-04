#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Items.h"
#include "../Header/Mario.h"

class GameEngine
{
    /*          Properties          */
private:
    Mario mario;
    Items counterCoin = Items(mario, COIN, 575, 38);
    Font headerFont;
    ostringstream scoreStr, timerStr, coinsStr;
    Clock timer, convertTimer;
    int currentTime, levelTime, counterTime, scoreInt, fontSize, coinsInt, remainTime;
    fstream playersFile;
    map<string, int> levelsMap;

public:
    Text timerText, scoreText, coinsText, levelText;

    /*         Constractar          */
    GameEngine();

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
    void draw(RenderWindow& window);


    // Increase coins counter by one
    void updateCoins();


    // Add player name , his score and level to Players file
    void addPlayerInfo(std::string playerName);


    // Set level Name text
    void setLevelName(std::string levelName);


    // Start Converting time to Score
    void startTimeToScore();
};

