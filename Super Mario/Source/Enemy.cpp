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
	accSpeed = 1;
	speed[0] = gameEngine.currentPlayer.enemiesSpeed * accSpeed;
	speed[1] = 70;
	enemyType = type;
	blackRect = IntRect(0, 0, 32, 31);
	smashedRect = IntRect(64, 0, 32, 31);
	turtleRect = IntRect(0, 34, 32, 46);
	shellRect = IntRect(64, 36, 32, 42);
	
	// Set item Sprite properties
	enemySprite.setTexture(gameEngine.enemyTextrue);
	enemySprite.setPosition(x, y);


	switch (enemyType) {
	case BLACK:
		enemyRect = blackRect;
		killScore = 100;
		scale = 1.8;
		break;
	case TURTLE:
		enemyRect = turtleRect;
		killScore = 400;
		scale = -1.8;
		break;
	default:
		killScore = 0;
		break;
	}

	enemySprite.setTextureRect(enemyRect);
	enemySprite.setOrigin(enemyRect.width / 2, enemyRect.height);
	enemySprite.setScale(scale, abs(scale));

	// Set Floating text properties
	floatingText.setFont(gameEngine.floatingTextFont);
	floatingText.setCharacterSize(20);
	floatingText.setStyle(Text::Bold);
	floatingText.setOrigin(9, 9);
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
	if(moving) enemySprite.move(speed[0], speed[1]);
	changeDirection();
	checkGround();
	checkKilled();
	TextFloat();
	if(enemyType == SHELL) checkTurtleFaid();
	if (firstTime && enemyType != SHELL) {
		speed[0] = gameEngine->currentPlayer.enemiesSpeed * accSpeed;
		firstTime = false;
	}
}


void Enemy::TextFloat() {
	if (faid) {
		if (!resetTime) {
			floatingText.setPosition(enemySprite.getPosition());
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

			if (enemyType == SHELL){
				if (firstTime) {
					resetTime = false;
					firstTime = false;
				}
				
				faid = false;
			} 
			else display = false;
		}
		floatingText.move(0, floatingSpeed);
	}
}


void Enemy::changeDirection() {
	if (enemySprite.getGlobalBounds().intersects(maxX->getGlobalBounds())) {
		enemySprite.setScale(-scale, abs(scale));
		speed[0] = -gameEngine->currentPlayer.enemiesSpeed * accSpeed;
		
	}
	if (enemySprite.getGlobalBounds().intersects(minX->getGlobalBounds())) {
		enemySprite.setScale(scale, abs(scale));
		speed[0] = gameEngine->currentPlayer.enemiesSpeed * accSpeed;
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
			if (gameEngine->mario.speed[1] > 1 || (enemyType == SHELL && firstTime)) { // from above
				isKilled = true;
				if (!moving && enemyType == SHELL) {
					moving = true;
					turtleTimer.restart();
				}
				else moving = false;
			}
			else {
				gameEngine->mario.startDie();
			}
		}
		if(isKilled) setKilled();
	}
}


void Enemy::setKilled() {
	if (isKilled) {
		gameEngine->killSound.play();
		switch (enemyType) {
		case BLACK:
			enemyType = SMASHED;
			enemyRect = smashedRect;
			CurrentRect = 0;
			maxRect = 1;
			break;
		case TURTLE:
			enemyType = SHELL;
			enemyRect = shellRect;
			CurrentRect = 0;
			maxRect = 4;
			accSpeed = 4;
			speed[0] = gameEngine->currentPlayer.enemiesSpeed * accSpeed;
			firstTime = true;
			break;
		}
		faid = true;
		isKilled = false;
		gameEngine->updateScore(killScore);
	}
}


void Enemy::checkTurtleFaid() {
	if (moving && turtleTimer.getElapsedTime().asSeconds() > 10)
		display = false;
}