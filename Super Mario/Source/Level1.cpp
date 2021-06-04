#include "../Header/Level1.h"


Level1::Level1(GameEngine& gameEngine) {
	// Set initial values
	this->gameEngine = &gameEngine;
	display = false;
	coinPosition[0] = { 200,500 };
	flowerPosition[0] = { 400,500 };
	mashroomPosition[0] = { 600,500 };

	// Call Constructer for all coins 
	for (int i = 0; i < COINS_NUM; i++) {
		coin.push_back(*new Items(gameEngine.mario, gameEngine, COIN, coinPosition[i].x, coinPosition[i].y));
	}

	// Call Constructer for all flowers
	for (int i = 0; i < FLOWERS_NUM; i++) {
		flower.push_back(*new Items(gameEngine.mario, gameEngine, FLOWER, flowerPosition[i].x, flowerPosition[i].y));
	}

	// Call Constructer for all mashrooms
	for (int i = 0; i < MASHROOMS_NUM; i++) {
		mashroom.push_back(*new Items(gameEngine.mario, gameEngine, MASHROOM, mashroomPosition[i].x, mashroomPosition[i].y));
	}

	// Set Level's Background Properties
	backGroundTexture.loadFromFile(LEVEL1_BACKGROUND);
	backGroundSprite.setTexture(backGroundTexture);
}


void Level1::draw(RenderWindow& window) {
	if (display) {
		window.draw(backGroundSprite);
		gameEngine->draw(window);
		gameEngine->mario.draw(window);
		for (int i = 0; i < COINS_NUM; i++) 
			coin[i].draw(window);

		for (int i = 0; i < FLOWERS_NUM; i++) 
			flower[i].draw(window);

		for (int i = 0; i < MASHROOMS_NUM; i++) 
			mashroom[i].draw(window);
	}
}


void Level1::catchEvents(Event event) {
	if (display) {
		gameEngine->mario.catchEvents(event);

		// Handle event that make user return back to Main Menu
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
			// Pause the game
			this->end();
		}
	}
}


void Level1::start() {
	display = true;
	gameEngine->startCountDown();
}


void Level1::end() {
	display = false;
}