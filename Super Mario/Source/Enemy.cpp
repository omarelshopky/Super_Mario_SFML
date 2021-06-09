#include "../Header/Enemy.h"

Enemy::Enemy(GameEngine& gameEngine, enemy_t type, Sprite& minX, Sprite& maxX, RectangleShape& ground, float x, float y) {
	// Set initial values
	this->gameEngine = &gameEngine;
	this->minX = &minX;
	this->maxX = &maxX;
	this->ground = &ground;
	display = moving = firstTime = true;
	faid = isKilled = resetTime = onGround = false;
	CurrentRect = floatingSpeed = 0;
	maxRect = 2;
	speed[0] = gameEngine.currentPlayer.enemiesSpeed;
	speed[1] = 70;
	enemyType = type;
	blackRect = IntRect(0, 0, 33, 31);
	smashedRect = IntRect(66, 0, 33, 31);
	turtleRect = IntRect(64, 40, 32, 41);
	shellRect = IntRect(64, 40, 32, 41);
	
	// Set item Sprite properties
	enemySprite.setTexture(gameEngine.enemyTextrue);
	enemySprite.setPosition(x, y);


	switch (enemyType) {
	case BLACK:
		enemyRect = blackRect;
		killScore = 100;
		break;
	case TURTLE:
		enemyRect = turtleRect;
		killScore = 400;
		break;
	default:
		killScore = 0;
		break;
	}

	enemySprite.setTextureRect(enemyRect);
	enemySprite.setOrigin(enemyRect.width / 2, enemyRect.height);
	enemySprite.setScale(1.8, 1.8);

	// Set Floating text properties
	floatingText.setFont(gameEngine.floatingTextFont);
	floatingText.setCharacterSize(20);
	floatingText.setStyle(Text::Bold);
	floatingText.setOrigin(9, 9);
	floatingText.setPosition(x, y);
	floatingText.setLetterSpacing(0.01);
	floatingText.setFillColor(Color(218, 18, 29));
	floatingText.setString(to_string(killScore));
}


void Enemy::draw(RenderWindow& window) {
	if (display) {
		animation();
		if (faid) window.draw(floatingText);
		window.draw(enemySprite);
	}
}


void Enemy::animation() {
	if (timer.getElapsedTime().asSeconds() > 0.2f) {
		switch (enemyType) {
		case BLACK:
			enemyRect.left = blackRect.left + CurrentRect * blackRect.width;
			break;
		case TURTLE:
			enemyRect.left = turtleRect.left + CurrentRect * turtleRect.width;
			break;
		case SHELL:
			enemyRect.left = shellRect.left + CurrentRect * shellRect.width;
			break;
		default:
			break;
		}
		enemySprite.setTextureRect(enemyRect);
		if(moving)CurrentRect++;

		if (CurrentRect == maxRect) CurrentRect = 0;

		timer.restart();
	}
	enemySprite.move(speed[0], speed[1]);
	changeDirection();
	checkGround();
	//checkKilled();
	//TextFloat();
	if (firstTime) {
		speed[0] = gameEngine->currentPlayer.enemiesSpeed;
		firstTime = false;
	}
}


void Enemy::TextFloat() {
	if (faid) {
		if (!resetTime) {
			textFloatTimer.restart();
			resetTime = true;
		}

		int currentTime = textFloatTimer.getElapsedTime().asMilliseconds();
		if (currentTime < 60)
		{
			floatingSpeed += -1;
		}
		else if (currentTime < 750)
		{
			floatingText.setFillColor(Color(219, 59, 78));
			floatingSpeed += -0.1;
		}
		else if (currentTime < 1100)
		{
			floatingText.setFillColor(Color(179, 116, 146));
			floatingSpeed += -0.1;
		}
		else
		{
			floatingText.setFillColor(Color::Transparent);
			floatingSpeed = 0; //Reseting its value
			display = false;
		}
		floatingText.move(0, floatingSpeed);
	}
}


void Enemy::changeDirection() {
	if (enemySprite.getGlobalBounds().intersects(maxX->getGlobalBounds())) {
		enemySprite.setScale(-1.8, 1.8);
		speed[0] = -gameEngine->currentPlayer.enemiesSpeed;
		
	}
	if (enemySprite.getGlobalBounds().intersects(minX->getGlobalBounds())) {
		enemySprite.setScale(1.8, 1.8);
		speed[0] = gameEngine->currentPlayer.enemiesSpeed;
	}
}


void Enemy::checkGround() {
	
	if (enemySprite.getGlobalBounds().intersects(ground->getGlobalBounds())) {
		speed[1] = 0;
		if(!onGround) enemySprite.setPosition(enemySprite.getPosition().x, ground->getGlobalBounds().top);
		onGround = true;
	}
	else {
		speed[1] = 70;
		onGround = false;
	}
}

void Enemy::checkKilled() {
	if (!gameEngine->mario.dying) {
		if (enemySprite.getGlobalBounds().intersects(gameEngine->mario.marioSprite.getGlobalBounds()) && !faid) {
			isKilled = true;
			switch (enemyType)
			{
			case COIN:
				gameEngine->coinSound.play();
				break;
			case MASHROOM:
			case FLOWER:
				gameEngine->powerUpSound.play();
				break;
			default:
				break;
			}
		}
		setKilled();
	}
}


void Enemy::setKilled() {
	if (isKilled) {
		gameEngine->killSound.play();
		switch (enemyType) {
		case BLACK:
			gameEngine->updateCoins(); // increase coin counter by one
			enemyType = SMASHED;
			enemyRect = smashedRect;
			CurrentRect = 0;
			maxRect = 1;
			break;
		case TURTLE:
			gameEngine->mario.PoweringUpToBig = true;
			break;
		case SHELL:
			gameEngine->mario.PoweringUpToSuper = true;
			break;
		}
		faid = true;
		isKilled = false;
		gameEngine->updateScore(killScore);
	}
}