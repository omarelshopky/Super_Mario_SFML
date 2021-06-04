#include "../Header/Blocks.h"

Blocks::Blocks(Mario& mario, block_t type, float x, float y) {
	// Set initial values
	this->mario = &mario;
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
	blockSprite.setScale(1.8, 1.8);
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
	checkIntersection();
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


void Blocks::checkIntersection() {
	bounds marioBounds, blockBounds;
	marioBounds.top = mario->marioSprite.getGlobalBounds().top;
	marioBounds.bottom = marioBounds.top + mario->marioSprite.getGlobalBounds().height;
	marioBounds.left = mario->marioSprite.getGlobalBounds().left;
	marioBounds.right = marioBounds.left + mario->marioSprite.getGlobalBounds().width;

	blockBounds.top = blockSprite.getGlobalBounds().top;
	blockBounds.bottom = blockBounds.top + blockSprite.getGlobalBounds().height;
	blockBounds.left = blockSprite.getGlobalBounds().left;
	blockBounds.right = blockBounds.left + blockSprite.getGlobalBounds().width;

	if (marioBounds.right >= blockBounds.left && marioBounds.right < blockBounds.right || marioBounds.left <= blockBounds.right && marioBounds.left > blockBounds.left) {
		if (marioBounds.bottom >= blockBounds.top && marioBounds.bottom < blockBounds.bottom) {
			mario->marioSprite.setPosition(mario->marioSprite.getPosition().x, blockBounds.top);
			mario->speed[1] = 0;
			mario->jumping = false;
		}
		else if (marioBounds.top <= blockBounds.bottom && marioBounds.bottom > blockBounds.bottom) {
			startPopUp();
		}
		else if (marioBounds.top > blockBounds.top && marioBounds.top < blockBounds.bottom){
			mario->marioSprite.setPosition(mario->marioSprite.getPosition().x, mario->marioSprite.getPosition().y);
			mario->speed[0] = 0;
			
		}




	}
}