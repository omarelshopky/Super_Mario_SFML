#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include<iomanip>

using namespace sf;
using namespace std;

class GameEngine
{
    /*          Properties          */
private:
    Font Header_Font;
    ostringstream Score_Str, Timer_Str;
    Clock Timer;
    int Current_Time, Level_Time, Counter_Time, Score_Int, Font_Size;

public:
    Text Timer_Text, Score_Text;
    RenderWindow *GameWindow;

    /*         Constractar          */
    GameEngine(RenderWindow& window);

    /*          Method         */
    
    // Update current score with Increased Score and display it
    void Update_Score(int IncScore);


    // Start timer
    void Start_CountDown();


    // Update timer
    void Update_Timer();


    // Check wheater Level time is finished or not
    bool isTimerFinished();
    

    // Convert remain time to score when player won
    void TimeToScore();


    // draw GameEngine objects into screen
    void Draw();
};

