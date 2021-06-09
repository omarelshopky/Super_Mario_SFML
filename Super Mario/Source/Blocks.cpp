#include "../Header/Blocks.h"

Blocks::Blocks(GameEngine& gameEngine, block_t blockType, item_t itemType, float x, float y) : item(gameEngine, itemType, x, y)
{
	// Set initial values
	this->gameEngine = &gameEngine;
	this->itemType = itemType;
	this->blockType = blockType;

	questionRect = IntRect(0, 0, 32, 31);
	stoneRect = IntRect(32, 0, 32, 31);
	bronzeRect = IntRect(0, 32, 32, 31);
	rockRect = IntRect(96, 0, 32, 31);
	smashRect = IntRect(0, 0, 800, 800);

	currentRect = movingSpeed = 0;
	display = true;
	item.display = false;
	faid = isPopUp = marioOn = stuckOn = popUpBlock = false;
	startPos.x = x;
	startPos.y = y;

	// Set Sprite Properties
	switch (blockType)
	{
	case QUESTION:
		blockSprite.setTexture(gameEngine.questionTexture);
		blockRect = questionRect;
		maxRect = 4;
		break;
	case STONE:
		blockSprite.setTexture(gameEngine.stoneTexture);
		blockRect = stoneRect;
		maxRect = 1;
		break;
	case ROCK:
		blockSprite.setTexture(gameEngine.stoneTexture);
		blockRect = rockRect;
		maxRect = 1;
		break;
	}

	blockSprite.setOrigin(blockRect.width / 2, blockRect.height / 2);
	blockSprite.setTextureRect(blockRect);
	blockSprite.setPosition(x, y);
	blockSprite.setScale(2, 2);
	blockHight = blockSprite.getGlobalBounds().height;
}


void Blocks::draw(RenderWindow& window) {
	item.draw(window);
	if (display) {
		animation();
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
			blockSprite.setTexture(gameEngine->stoneTexture);
			blockRect = bronzeRect;
			maxRect = 1;
			break;
		case STONE:
			blockRect = stoneRect;
			break;
		case ROCK:
			blockRect = rockRect;
			break;
		case SMASH:
			if (!faid) {
				maxRect = 6;
				currentRect = 0;
				blockRect = smashRect;
				blockSprite.setOrigin(400, 400);
				blockSprite.setTexture(gameEngine->smashTextures[currentRect]);
				blockSprite.setScale(1, 1);
				faid = true;
			}
			else {
				blockSprite.setTexture(gameEngine->smashTextures[currentRect]);
				if (currentRect == maxRect - 1) display = false;
			}
		}

		blockSprite.setTextureRect(blockRect);
		currentRect++;

		if (currentRect == maxRect) currentRect = 0;

		timer.restart();
	}
	popUp();
	if(!faid) checkIntersection();
}

void Blocks::smash() {
	blockType = SMASH;
	gameEngine->smashSound.play();
}

void Blocks::startPopUp() {
	if (!isPopUp) {
		isPopUp = true;
		popUpBlock = true;
		
		popUpTimer.restart();
		gameEngine->popUpSound.play();
	}
}


void Blocks::popUp() {
	if (isPopUp) {
		int currentTime = popUpTimer.getElapsedTime().asMilliseconds();

		if (currentTime < 150) // GoingUp Time
		{
			if(popUpBlock) movingSpeed += -1;
			else {
				if (itemType == COIN) movingSpeed += -3;
				else movingSpeed += -1.05;
			}
		}
		else if (currentTime < 200) // StandStill time
		{
			movingSpeed = 0;
			if (itemType == MASHROOM || itemType == FLOWER) movingSpeed += -1;
		}
		else if (currentTime < 350) // GoingDown Time
		{
			if (popUpBlock) movingSpeed += 1;
			else {
				if (itemType == COIN) movingSpeed += 1.15;
			}
		}
		else 
		{
			if (blockType == QUESTION) blockType = BRONZE;

			movingSpeed = 0;
			if (!popUpBlock) {
				isPopUp = false; // finish all pop up 
				item.blockPoped = true; // when its coin its take itself
				item.itemSprite.setPosition(startPos.x, startPos.y - (blockHight / 2) - (item.itemHeight / 2));
			}
			if (popUpBlock){
				popUpBlock = false; // start item pop up 
				if (itemType == MASHROOM || itemType == FLOWER) gameEngine->powerUpAppearSound.play(); // start sound effect
				item.display = true;
			}
			
			blockSprite.setPosition(startPos.x, startPos.y);
			popUpTimer.restart();
		}
		if(popUpBlock) // blocks pop up
			blockSprite.move(0, movingSpeed);
		else // item pop up
			item.itemSprite.move(0, movingSpeed);
	}
}


void Blocks::checkIntersection() {
	// Calculate Mario and Block bounds
	FloatRect marioBounds = gameEngine->mario.marioSprite.getGlobalBounds(),
		blockBounds = blockSprite.getGlobalBounds();
	Vector2f marioPos = gameEngine->mario.marioSprite.getPosition(), blockPos = blockSprite.getPosition();

	float blockTopPoint = blockPos.y - (blockBounds.height / 2),
		blockBottomPoint = blockPos.y + (blockBounds.height / 2),
		blockRightPoint = blockPos.x + (blockBounds.width / 2),
		blockLeftPoint = blockPos.x - (blockBounds.width / 2);
	
	// In the block bounds
	if (blockBounds.intersects(marioBounds)) {
		if (marioPos.x >= blockLeftPoint && marioPos.x <= blockRightPoint) {
			if (gameEngine->mario.speed[1] > 0 && blockType != SMASH) { // jump on the block
				gameEngine->mario.marioSprite.setPosition(marioPos.x, blockBounds.top);
				gameEngine->mario.onGround = true;
				marioOn = true;
			}
			else if (gameEngine->mario.speed[1] < 0/*marioPos.y - (marioBounds.height/2) >= blockBottomPoint*/) { // Hit the block with head
				float blockBottom = blockBounds.top + blockBounds.height;

				// Handle large size of smash sprite
				if (blockType == SMASH) blockBottom = (blockBounds.top + blockBottom) / 2;

				gameEngine->mario.marioSprite.setPosition(marioPos.x, blockBottom + marioBounds.height);
				gameEngine->mario.speed[1] = 2;
				handleHitBlock();
			}
		}
		else { // touch from side
			if (gameEngine->mario.speed[1] > 1 && !gameEngine->mario.onGround || gameEngine->mario.speed[1] < 1) {
				float blockRight = blockBounds.left + blockBounds.width;
				if (marioPos.x > blockPos.x)
					gameEngine->mario.marioSprite.setPosition(blockRight + (marioBounds.width / 2), marioPos.y);
				else
					gameEngine->mario.marioSprite.setPosition(blockBounds.left - (marioBounds.width / 2), marioPos.y);
				gameEngine->mario.speed[0] = 0;
				gameEngine->mario.stuck = true;
				stuckOn = true;
			}
		}
	}
	else {
		if (marioOn && gameEngine->mario.onGround) { // Fall when mario left the block
			marioOn = false;
			gameEngine->mario.onGround = false;
			gameEngine->mario.speed[1] = -5;
		}

		// Fix Screen vibration when mario touch block side
		if (gameEngine->mario.stuck && stuckOn) {
			if (abs(marioPos.x - blockPos.x) > 60 || abs(marioPos.y - blockPos.y) > 100) {
				gameEngine->mario.stuck = false; // not touching the side anymore
				stuckOn = false;
			}
		}
	}
}


void Blocks::handleHitBlock() {
	switch (blockType)
	{
	case STONE:
		switch (gameEngine->mario.marioState) {
		case SMALL:
			startPopUp();
			break;
		case BIG:
		case SUPER:
			smash();
			break;
		}
		break;
	case QUESTION:
		startPopUp();
		break;
	default:
		break;
	}
}