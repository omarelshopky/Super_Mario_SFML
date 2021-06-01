#include "../Header/Blocks.h"

Blocks::Blocks(block_t type, float x, float y) {
	// Set initial values
	questionRect = IntRect(0, 0, 32, 32);
	stoneRect = IntRect(32, 0, 32, 32);
	bronzeRect = IntRect(0, 32, 32, 32);
	smashRect = IntRect(0, 0, 800, 800);

	currentRect = movingSpeed = 0;
	display = true;
	faid = isPopUp = false;
	blockType = type;
	startPos.x = x;
	startPos.y = y;

	// Load Textures form files
	questionTexture.loadFromFile(QUESTION_BLOCK);
	questionTexture.setSmooth(true);

	stoneTexture.loadFromFile(STONE_BLOCK);
	stoneTexture.setSmooth(true);

	for (int i = 0; i < 6; i++) {
		smashTextures[i].loadFromFile(SMASH_STONE_BLOCK + to_string(i) + ".png");
		smashTextures[i].setSmooth(true);
	}

	switch (type)
	{
	case QUESTION:
		blockSprite.setTexture(questionTexture);
		blockRect = questionRect;
		maxRect = 4;
		break;
	case STONE:
		blockSprite.setTexture(stoneTexture);
		blockRect = stoneRect;
		maxRect = 1;
		break;
	}

	// Set sprite properties
	blockSprite.setOrigin(16, 16);
	blockSprite.setTextureRect(blockRect);
	blockSprite.setPosition(x, y);
	blockSprite.setScale(1.5, 1.5);
}


void Blocks::draw(RenderWindow& window) {
	animation();
	if (display) {
		window.draw(blockSprite);
	}

}


void Blocks::animation() {
	if (timer.getElapsedTime().asSeconds() > 0.2f) {
		switch (blockType) {
		case QUESTION:
			blockRect.left = questionRect.left + currentRect * questionRect.width;
			break;
		case BRONZE:
			blockRect = bronzeRect;
			maxRect = 1;
			break;
		case STONE:
			blockRect = stoneRect;
			break;
		case SMASH:
			if (!faid) {
				maxRect = 6;
				currentRect = 0;
				blockRect = smashRect;
				blockSprite.setOrigin(400, 400);
				blockSprite.setTexture(smashTextures[currentRect]);
				faid = true;
			}
			else {
				blockSprite.setTexture(smashTextures[currentRect]);
				if (currentRect == maxRect - 1) display = false;
			}
		}

		blockSprite.setTextureRect(blockRect);
		currentRect++;

		if (currentRect == maxRect) currentRect = 0;

		timer.restart();
	}
	popUp();
}

void Blocks::smash() {
	blockType = SMASH;
}

void Blocks::startPopUp() {
	isPopUp = true;
	popUpTimer.restart();
}


void Blocks::popUp() {
	if (isPopUp) {
		int currentTime = popUpTimer.getElapsedTime().asMilliseconds();

		if (currentTime < 150) // GoingUp Time
		{
			movingSpeed += -1;
		}
		else if (currentTime < 200) // StandStill time
		{
			movingSpeed = 0;
		}
		else if (currentTime < 350) // GoingDown Time
		{
			movingSpeed += 1;
		}
		else 
		{
			movingSpeed = 0;
			isPopUp = false;
			blockSprite.setPosition(startPos.x, startPos.y);
			popUpTimer.restart();
		}
		blockSprite.move(0, movingSpeed);
	}
}