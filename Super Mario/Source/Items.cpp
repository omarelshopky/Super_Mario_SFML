#include "../Header/Items.h"

Items::Items(Mario& mario, GameEngine& gameEngine, item_t item, float x, float y) {
	// Set initial values
	this->mario = &mario;
	this->gameEngine = &gameEngine;
	display = true;
	faid = isTaken = resetTime = false;
	CurrentRect = floatingSpeed =  0;
	itemType = item;
	coinIntRect = IntRect(0, 86, 33, 30);
	flowerIntRect = IntRect(32, 213, 32, 30);
	mashroomIntRect = IntRect(128, 150, 32.5, 45);
	sparklsIntRect = IntRect(0, 116, 40, 32);

	// Set item Sprite properties
	itemTexture.loadFromFile(ITEMS);
	itemSprite.setTexture(itemTexture);
	itemSprite.setPosition(x, y);
	itemSprite.setScale(1.5, 1.5);

	switch (itemType) {
	case COIN:
		maxRect = 4;
		itemIntRect = coinIntRect;
		takenScore = 100;
		takenSoundBuffer.loadFromFile(COIN_SOUND);
		break;
	case FLOWER:
		maxRect = 3;
		itemIntRect = flowerIntRect;
		takenScore = 1500;
		takenSoundBuffer.loadFromFile(POWERUP_SOUND);
		break;
	case MASHROOM:
		maxRect = 2;
		itemIntRect = mashroomIntRect;
		takenScore = 1000;
		takenSoundBuffer.loadFromFile(POWERUP_SOUND);
		break;
	}

	itemSprite.setTextureRect(itemIntRect);
	itemSprite.setOrigin(itemIntRect.width / 2, itemIntRect.height / 2);

	takenSound.setBuffer(takenSoundBuffer);

	// Set Floating text properties
	font.loadFromFile(FLOATING_FONT);
	floatingText.setFont(font);
	floatingText.setCharacterSize(20);
	floatingText.setStyle(Text::Bold);
	floatingText.setOrigin(9, 9);
	floatingText.setPosition(x, y);
	floatingText.setLetterSpacing(0.01);
	floatingText.setFillColor(Color(218, 18, 29));
	floatingText.setString(to_string(takenScore));
}


void Items::draw(RenderWindow& window) {
	animation();
	if (display) {
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
	if (!mario->dying) {
		if (itemSprite.getGlobalBounds().intersects(mario->marioSprite.getGlobalBounds()) && !faid) {
			isTaken = true;
			takenSound.play();
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
			CurrentRect = 0;
			maxRect = 6;
			break;
		case MASHROOM:
			mario->PoweringUpToBig = true;
			break;
		case FLOWER:
			mario->PoweringUpToSuper = true;
			break;
		}
		faid = true;
		isTaken = false;
		gameEngine->updateScore(takenScore);
		
	}
}