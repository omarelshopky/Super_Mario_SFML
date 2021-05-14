#include "../Header/GameEngine.h"


GameEngine::GameEngine() {
	// Set initial values
	Level_Time = 300;
	Score_Int = 0, Current_Time = 0, Counter_Time = 0;
	Score_Str << "MARIO: 000000";
	Font_Size = 45;

	// Load font from file
	Header_Font.loadFromFile("Resource/Fonts/some_font.ttf");
	
	// set Score Text properties
	Score_Text.setFont(Header_Font);
	Score_Text.setCharacterSize(Font_Size);
	Score_Text.setPosition(20, 5);
	Score_Text.setString(Score_Str.str());

	// set Timer Text Properties
	Timer_Text.setPosition(1395,5);
	Timer_Text.setCharacterSize(Font_Size);
	Timer_Text.setFont(Header_Font);
}


void GameEngine::Update_Score(int IncScore) {
	// Increase current score
	Score_Int += IncScore;
	// clear score_str
	Score_Str.str(string());
	Score_Str << "MARIO: " << setw(6) << setfill('0') << Score_Int;
	Score_Text.setString(Score_Str.str());
}


void GameEngine::Start_CountDown() {
	Timer.restart();
}


void GameEngine::Update_Timer(int Counter) {
	Counter_Time = Counter;

	// clear timer_str
	Timer_Str.str(string());
	Current_Time = Timer.getElapsedTime().asSeconds();
	
	// if we didn't provide an argument calculate Time
	if (Counter_Time == -1) {
		Counter_Time = Level_Time - Current_Time;
	}
	else {/*  Do Nothing  */ }

	if (Counter_Time >= 0) {
		Timer_Str << "TIME: " << setw(3) << setfill('0') << Counter_Time;
		Timer_Text.setString(Timer_Str.str());
	}
	else{/* Do Nothing */ }
}


bool GameEngine::isTimerFinished() {
	if (Counter_Time == 0)
		return true;
	else
		return false;
}


void GameEngine::TimeToScore() {
	for (int x = Counter_Time; x > 0; x--) {
		Update_Timer(x);
		Update_Score(50);
	}
}