#include "../Header/Level1.h"


Level1::Level1(GameEngine& gameEngine) {
	// Set initial values
	this->gameEngine = &gameEngine;
	display = false;
	coinPosition[0] = { 200,500 };
	flowerPosition[0] = { 400,500 };
	mashroomPosition[0] = { 600,500 };
	gameEngine.setLevelName("Level 1");

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
	backGroundTexture.setRepeated(true);
	backGroundShape.setTexture(&backGroundTexture);
	backGroundShape.setSize(Vector2f(3000, 900));

	// Set Level's Ground Properties
	groundTexture.loadFromFile(LEVEL1_GROUND);
	groundTexture.setRepeated(true);
	groundShape.setTexture(&groundTexture);
	groundShape.setSize(Vector2f(3000, 150));
	groundShape.setPosition(0, 750);

	// Set View Properites
	camera.setSize(1600, 900);
	camera.setCenter(800, 450);
}


void Level1::draw(RenderWindow& window) {
	if (display) {
		camera.setCenter(gameEngine->mario.marioSprite.getPosition().x, 450);
		window.setView(camera);
		window.draw(backGroundShape);
		window.draw(groundShape);
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
		switch (event.type)
		{
		case Event::KeyPressed:
			switch (event.key.code)
			{
			/*case Keyboard::Right:
				camera.move(15, 0);
				break;
			case Keyboard::Left:
				camera.move(-15, 0);
				break;*/
			case Keyboard::Escape:
				this->end();
				break;
			}
			break;
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