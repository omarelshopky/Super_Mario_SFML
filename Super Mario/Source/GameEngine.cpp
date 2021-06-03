#include "../Header/GameEngine.h"


GameEngine::GameEngine() {
	// Set initial values
	startTimeToScore = false;
	levelTime = 300;
	scoreInt = coinsInt = currentTime = remainTime = counterTime = 0;
	scoreStr << "MARIO: 000000";
	coinsStr << "x00";
	fontSize = 45;
	
	// Load font from file
	if(!headerFont.loadFromFile(GAME_HEADER_FONT)) { std::cout << "Can't load GAME_HEADER_FONT\n"; }
	
	// set Score Text properties
	scoreText.setPosition(20, 5);
	scoreText.setFont(headerFont);
	scoreText.setCharacterSize(fontSize);
	scoreText.setString(scoreStr.str());

	// set Timer Text Properties
	timerText.setPosition(1395,5);
	timerText.setFont(headerFont);
	timerText.setCharacterSize(fontSize);

	// Set Coins Text Properties
	coinsText.setPosition(600, 5);
	coinsText.setFont(headerFont);
	coinsText.setCharacterSize(fontSize);
	coinsText.setString(coinsStr.str());

	// Set Level name Text Properties
	levelText.setPosition(1000, 5);
	levelText.setFont(headerFont);
	levelText.setCharacterSize(fontSize);
	levelText.setStyle(Text::Bold);

	// Set levels Map values
	levelsMap["level 1"] = 1;
	levelsMap["level 2"] = 2;
}


void GameEngine::updateScore(int IncScore) {
	// Increase current score
	scoreInt += IncScore;
	// clear score_str
	scoreStr.str(string());
	scoreStr << "MARIO: " << setw(6) << setfill('0') << scoreInt;
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


void GameEngine::updateCoins() {
	coinsInt++;
	coinsStr.str(string());
	coinsStr << "x" << setw(2) << setfill('0') << coinsInt;
	coinsText.setString(coinsStr.str());
}


bool GameEngine::isTimerFinished() {
	if (counterTime == 0)
		return true;
	else
		return false;
}


void GameEngine::timeToScore() {
	// Start convert Time to Score
	if (!startTimeToScore) {
		remainTime = counterTime;
		startTimeToScore = true;
	}
	
	if (remainTime >= 0) {
		if (convertTimer.getElapsedTime().asMilliseconds() >= 6) {
			levelTime = remainTime;
			updateTimer();
			updateScore(50);

			remainTime--;

			timer.restart();
			convertTimer.restart();
		}
	}
}


void GameEngine::draw() {
	gameWindow->draw(scoreText);
	gameWindow->draw(timerText);
	gameWindow->draw(coinsText);
	gameWindow->draw(levelText);
}


void GameEngine::setLevelName(string levelName) {
	levelText.setString(levelName);
}


void GameEngine::addPlayerInfo(string playerName) {
	playersFile.open(PLAYERS_FILE, ios::app);
	playersFile << playerName << ' ' << scoreInt << ' ' << levelsMap[std::string(levelText.getString())] << '\n';
	playersFile.close();
	playersFile.clear();
}




