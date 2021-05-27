#pragma once
#include <SFML/Graphics.hpp>
#include "../Header/DEFINITION.h"
#include <sstream>
#include<iomanip>

using namespace sf;
using namespace std;

class GameEngine
{
    /*          Properties          */
private:
    Font headerFont;
    ostringstream scoreStr, timerStr;
    Clock timer;
    int currentTime, levelTime, counterTime, scoreInt, fontSize;

public:
    Text timerText, scoreText;
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
};

