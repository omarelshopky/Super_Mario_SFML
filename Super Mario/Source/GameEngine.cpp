#include "../Header/GameEngine.h"


GameEngine::GameEngine() : mario(500, 200){
	// Set initial values
	levelTime = 300;
	scoreInt = coinsInt = currentTime = counterTime = 0;
	remainTime = -1;
	scoreStr << "MARIO: 000000";
	coinsStr << "x00";
	fontSize = 45;
	lifeScreen = gameRunning = false;

	// Load font from file
	if(!headerFont.loadFromFile(GAME_HEADER_FONT)) { std::cout << "Can't load GAME_HEADER_FONT\n"; }
	floatingTextFont.loadFromFile(FLOATING_FONT);

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

	// Set Coin Sprite Properties
	coinRect = IntRect(0, 86, 33, 30);
	coinTexture.loadFromFile(ITEMS);
	coinSprite.setTexture(coinTexture);
	coinSprite.setTextureRect(coinRect);
	coinSprite.setPosition(575, 38);
	coinSprite.setScale(1.5, 1.5);
	coinSprite.setOrigin(coinRect.width / 2, coinRect.height / 2);

	// Set Level name Text Properties
	levelText.setPosition(1000, 5);
	levelText.setFont(headerFont);
	levelText.setCharacterSize(fontSize);
	levelText.setStyle(Text::Bold);

	// Set levels Map values
	levelsMap["level 1"] = 1;
	levelsMap["level 2"] = 2;

	//Set Lifes Text Properties
	lifeText.setCharacterSize(50);
	lifeText.setFont(headerFont);
	lifeText.setPosition(820, 420);
	lifeStr << "x" << currentPlayer.lifes;
	lifeText.setString(lifeStr.str());

	// Set Mario Sprite Properties
	marioLifeSprite.setTexture(mario.marioTexture);
	marioLifeSprite.setTextureRect(IntRect(0, 96, 28, 32));
	marioLifeSprite.setScale(2, 2);
	marioLifeSprite.setOrigin(14, 16);
	marioLifeSprite.setPosition(780, 450);

	// Load Game Sound Effects
	popUpBuffer.loadFromFile(POPUP_SOUND);
	popUpSound.setBuffer(popUpBuffer);

	smashBuffer.loadFromFile(SMASH_SOUND);
	smashSound.setBuffer(smashBuffer);

	coinBuffer.loadFromFile(COIN_SOUND);
	coinSound.setBuffer(coinBuffer);

	powerUpBuffer.loadFromFile(POWERUP_SOUND);
	powerUpSound.setBuffer(powerUpBuffer);

	killBuffer.loadFromFile(KILL_SOUND);
	killSound.setBuffer(killBuffer);

	if (!powerUpAppearBuffer.loadFromFile(POWERUP_APPEAR_SOUND)) { cout << "faild to load powerup appear\n"; }
	powerUpAppearSound.setBuffer(powerUpAppearBuffer);

	// Load Game Textures
	questionTexture.loadFromFile(QUESTION_BLOCK);
	stoneTexture.loadFromFile(STONE_BLOCK);
	itemTexture.loadFromFile(ITEMS);
	enemyTextrue.loadFromFile(ENEMY);

	for (int i = 0; i < 6; i++) {
		smashTextures[i].loadFromFile(SMASH_STONE_BLOCK + to_string(i) + ".png");
	}
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
	else {/* Do Nothing */ }

	if (counterTime == 0 && remainTime == -1) mario.startDie();
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
	if (remainTime > 0) {
		if (convertTimer.getElapsedTime().asMilliseconds() >= 6) {
			remainTime--;
			levelTime = remainTime;

			updateTimer();
			updateScore(50);

			timer.restart();
			convertTimer.restart();
		}
	}
}


void GameEngine::startTimeToScore() {
	remainTime = counterTime;
}


void GameEngine::draw(RenderWindow& window) {
	coinAnimation();
	updateTimer();
	updateLifes();

	window.draw(scoreText);
	window.draw(timerText);
	window.draw(coinsText);
	window.draw(levelText);
	window.draw(coinSprite);

	if (lifeScreen) startLifeScreen(window);
}


void GameEngine::startLifeScreen(RenderWindow& window) {
	Clock lifeScreenClock;
	while (lifeScreenClock.getElapsedTime().asSeconds() < 3) {
		window.clear();
		window.draw(scoreText);
		window.draw(timerText);
		window.draw(coinsText);
		window.draw(levelText);
		window.draw(coinSprite);
		window.draw(lifeText);
		window.draw(marioLifeSprite);
		window.display();
	}
	lifeScreen = false;
}



void GameEngine::setLevelName(string levelName) {
	levelText.setString(levelName);
}


void GameEngine::addPlayerInfo() {
	playersFile.open(PLAYERS_FILE, ios::app);
	playersFile << currentPlayer.name << ' ' << scoreInt << ' ' << levelsMap[std::string(levelText.getString())] << '\n';
	playersFile.close();
	playersFile.clear();
}


void GameEngine::coinAnimation() {
	if (coinTimer.getElapsedTime().asSeconds() > 0.2f) {
		coinRect.left += 33;
		if (coinRect.left > 99) coinRect.left = 0;

		coinSprite.setTextureRect(coinRect);
		coinTimer.restart();
	}

}


void GameEngine::setHeaderPosition(position screenCenter) {
	float topLeft = screenCenter.x - (WINDOW_WIDTH / 2);
	scoreText.setPosition(topLeft + 20, 5); //Score
	timerText.setPosition(topLeft + 1395, 5); // Timer
	coinsText.setPosition(topLeft + 600, 5); // Coins Counter
	coinSprite.setPosition(topLeft + 575, 38); // Coin sprite
	levelText.setPosition(topLeft + 1000, 5); // Level Name
	lifeText.setPosition(topLeft + 820, 420);
	marioLifeSprite.setPosition(topLeft + 780, 450);
}


void GameEngine::updateLifes() {
	lifeStr.str(string());
	if (mario.dead) {
		if (currentPlayer.lifes > 0) {
			currentPlayer.lifes--;
			lifeStr << "x" << currentPlayer.lifes;
		}
		else {
			lifeStr << "Game Over";
			gameRunning = false;
		}
		mario.dead = false;
		lifeScreen = true;
	}
	
	lifeText.setString(lifeStr.str());
} 