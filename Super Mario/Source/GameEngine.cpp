#include "../Header/GameEngine.h"


GameEngine::GameEngine(RenderWindow& window) {
	gameWindow = &window;

	// Set initial values
	levelTime = 300;
	scoreInt = 0, currentTime = 0, counterTime = 0;
	scoreStr << "MARIO: 0000000";
	fontSize = 45;

	// Load font from file
	if(!headerFont.loadFromFile(GAME_HEADER_FONT)) { std::cout << "Can't load GAME_HEADER_FONT\n"; }
	
	// set Score Text properties
	scoreText.setFont(headerFont);
	scoreText.setCharacterSize(fontSize);
	scoreText.setPosition(20, 5);
	scoreText.setString(scoreStr.str());

	// set Timer Text Properties
	timerText.setPosition(1395,5);
	timerText.setCharacterSize(fontSize);
	timerText.setFont(headerFont);
}


void GameEngine::updateScore(int IncScore) {
	// Increase current score
	scoreInt += IncScore;
	// clear score_str
	scoreStr.str(string());
	scoreStr << "MARIO: " << setw(7) << setfill('0') << scoreInt;
	scoreText.setString(scoreStr.str());
}


void GameEngine::startCountDown() {
	timer.restart();
}


void GameEngine::updateTimer() {
	// clear timer_str
	timerStr.str(string());
	currentTime = timer.getElapsedTime().asSeconds();
	counterTime = levelTime - currentTime;
	
	if (counterTime >= 0) {
		timerStr << "TIME: " << setw(3) << setfill('0') << counterTime;
		timerText.setString(timerStr.str());
	}
	else{/* Do Nothing */ }
}


bool GameEngine::isTimerFinished() {
	if (counterTime == 0)
		return true;
	else
		return false;
}


void GameEngine::timeToScore() {
	Clock clock;
	int x = counterTime;
	while (x >= 0) {
		if (clock.getElapsedTime().asMilliseconds() >= 6) {
			timer.restart();
			clock.restart();
			levelTime = x;
			updateTimer();
			updateScore(50);

			gameWindow->clear();
			draw();
			gameWindow->display();

			x--;
		}
	}
}


void GameEngine::draw() {
	gameWindow->draw(scoreText);
	gameWindow->draw(timerText);
}