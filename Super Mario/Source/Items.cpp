#include "../Header/Items.h"

Items::Items(GameEngine& gameEngine, item_t item, float x, float y) {
	// Set initial values
	this->gameEngine = &gameEngine;
	display = true;
	faid = isTaken = resetTime = blockPoped = false;
	CurrentRect = floatingSpeed = 0;
	itemType = item;
	coinIntRect = IntRect(0, 86, 32, 30);
	flowerIntRect = IntRect(32, 213, 32, 30);
	mashroomIntRect = IntRect(128, 150, 32.5, 32);
	sparklsIntRect = IntRect(0, 116, 40, 32);

	// Set item Sprite properties
	itemSprite.setTexture(gameEngine.itemTexture);
	itemSprite.setPosition(x, y);
	

	switch (itemType) {
	case COIN:
		maxRect = 4;
		itemIntRect = coinIntRect;
		takenScore = 100;
		break;
	case FLOWER:
		maxRect = 3;
		itemIntRect = flowerIntRect;
		takenScore = 1500;
		break;
	case MASHROOM:
		maxRect = 2;
		itemIntRect = mashroomIntRect;
		takenScore = 1000;
		break;
	case NONE:
		maxRect = 0;
		itemIntRect = IntRect(0, 0, 0, 0);
		takenScore = 0;
		break;
	}

	itemSprite.setTextureRect(itemIntRect);
	itemSprite.setOrigin(itemIntRect.width / 2, itemIntRect.height / 2);
	itemSprite.setScale(1.8, 1.8);
	itemHeight = itemSprite.getGlobalBounds().height;

	// Set Floating text properties
	floatingText.setFont(gameEngine.floatingTextFont);
	floatingText.setCharacterSize(20);
	floatingText.setStyle(Text::Bold);
	floatingText.setOrigin(9, 9);
	floatingText.setPosition(x, y);
	floatingText.setLetterSpacing(0.01);
	floatingText.setFillColor(Color(218, 18, 29));
	floatingText.setString(to_string(takenScore));
}


void Items::draw(RenderWindow& window) {
	if (display && itemType != NONE) {
		animation();
		if(faid) window.draw(floatingText);
		window.draw(itemSprite);
	}
}


void Items::animation() {
	if (timer.getElapsedTime().asSeconds() > 0.2f) {
		switch (itemType) {
		case COIN:
			itemIntRect.left = coinIntRect.left + CurrentRect * coinIntRect.width;
			break;
		case FLOWER:
			itemIntRect.left = flowerIntRect.left + CurrentRect * flowerIntRect.width;
			if (faid) itemSprite.setColor(Color::Transparent);
			break;
		case MASHROOM:
			itemIntRect.left = mashroomIntRect.left + CurrentRect * mashroomIntRect.width;
			if (faid) itemSprite.setColor(Color::Transparent);
			break;
		case SPARKL:
			itemIntRect.left = sparklsIntRect.left + CurrentRect * sparklsIntRect.width;
			if (CurrentRect == maxRect - 1) itemSprite.setColor(Color::Transparent);
			break;
		}
		itemSprite.setTextureRect(itemIntRect);
		CurrentRect++;

		if (CurrentRect == maxRect) CurrentRect = 0;

		timer.restart();
	}
	checkTaken();
	TextFloat();
}


void Items::TextFloat() {
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


void Items::checkTaken() {
	if (!gameEngine->mario.dying) {
		if (itemSprite.getGlobalBounds().intersects(gameEngine->mario.marioSprite.getGlobalBounds()) && !faid || (blockPoped && itemType == COIN)) {
			isTaken = true;
			switch (itemType)
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
		setTaken();
	}
}


void Items::setTaken() {
	if (isTaken) {
		switch (itemType) {
		case COIN:
			gameEngine->updateCoins(); // increase coin counter by one
			itemType = SPARKL; 
			itemIntRect = sparklsIntRect;
			itemSprite.setOrigin(itemIntRect.width / 2, itemIntRect.height / 2);
			CurrentRect = 0;
			maxRect = 6;
			break;
		case MASHROOM:
			gameEngine->mario.PoweringUpToBig = true;
			break;
		case FLOWER:
			gameEngine->mario.PoweringUpToSuper = true;
			break;
		}
		faid = true;
		isTaken = false;
		gameEngine->updateScore(takenScore);
	}
}