#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Mario.h"

class GameEngine
{
    /*          Properties          */
private:
    Font headerFont;
    ostringstream scoreStr, timerStr, coinsStr;
    Clock timer, convertTimer, coinTimer;
    int currentTime, levelTime, counterTime, scoreInt, fontSize, coinsInt, remainTime;
    fstream playersFile;
    map<string, int> levelsMap;
    Texture coinTexture;
    Sprite coinSprite;
    IntRect coinRect;

public:
    Mario mario;
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


    // make coin spin during time
    void coinAnimation();


    // Set header position to move with Camera
    void setHeaderPosition(position screenCenter);
};

