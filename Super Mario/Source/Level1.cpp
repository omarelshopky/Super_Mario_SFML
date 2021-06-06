#include "../Header/Level1.h"


Level1::Level1(GameEngine& gameEngine) {
	// Set initial values
	this->gameEngine = &gameEngine;
	display = marioOnGround = false;
	levelWidth = 3000;
	coinPosition[0] = { 200,500 };
	flowerPosition[0] = { 400,500 };
	mashroomPosition[0] = { 600,500 };
	stonePostition[0] = { 800, 500 };
	questionPosition[0] = { 1000, 720 };

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

	// Call Constructer for all Stone Blocks
	for (int i = 0; i < STONE_NUM; i++) {
		stone.push_back(*new Blocks(gameEngine.mario, STONE, stonePostition[i].x, stonePostition[i].y));
	}

	// Call Constructer for all Question Blocks
	for (int i = 0; i < QUESTION_NUM; i++) {
		question.push_back(*new Blocks(gameEngine.mario, QUESTION, questionPosition[i].x, questionPosition[i].y));
	}

	// Set Level's Background Properties
	backGroundTexture.loadFromFile(LEVEL1_BACKGROUND);
	backGroundTexture.setRepeated(true);
	backGroundShape.setTexture(&backGroundTexture);
	backGroundShape.setSize(Vector2f(levelWidth, WINDOW_HEIGHT));

	// Set Level's Ground Properties
	groundTexture.loadFromFile(LEVEL1_GROUND);
	groundTexture.setRepeated(true);
	groundShape.setTexture(&groundTexture);
	groundShape.setSize(Vector2f(3000, 150));
	groundShape.setPosition(0, 750);

	// Set View Properites
	camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	camera.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}


void Level1::draw(RenderWindow& window) {
	if (display) {
		checkGround();
		checkEnd();
		handleView(window);
		window.draw(backGroundShape);
		window.draw(groundShape);
		gameEngine->draw(window);
		for (int i = 0; i < COINS_NUM; i++) 
			coin[i].draw(window);

		for (int i = 0; i < FLOWERS_NUM; i++) 
			flower[i].draw(window);

		for (int i = 0; i < MASHROOMS_NUM; i++) 
			mashroom[i].draw(window);

		for (int i = 0; i < STONE_NUM; i++)
			stone[i].draw(window);

		for (int i = 0; i < QUESTION_NUM; i++)
			question[i].draw(window);

		gameEngine->mario.draw(window);
	}
}


void Level1::catchEvents(Event event) {
	if (display) {
		gameEngine->mario.catchEvents(event);
		
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
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


void Level1::checkGround(){
	if (!gameEngine->mario.dying) {
		if (groundShape.getGlobalBounds().intersects(gameEngine->mario.marioSprite.getGlobalBounds())) {
			gameEngine->mario.marioSprite.setPosition(gameEngine->mario.marioSprite.getPosition().x, groundShape.getGlobalBounds().top);
			gameEngine->mario.onGround = true;
		}
		else {
			if (marioOnGround && gameEngine->mario.onGround) {
				marioOnGround = false;
				gameEngine->mario.onGround = false;
				gameEngine->mario.speed[1] = -5;
			}
		}
	}
}


void Level1::handleView(RenderWindow& window) {
	if (!gameEngine->mario.stuck) { 
		position screenCenter = { gameEngine->mario.marioSprite.getPosition().x, 450 };

		if (screenCenter.x > WINDOW_WIDTH / 2 && screenCenter.x < levelWidth - (WINDOW_WIDTH / 2)) {
			camera.setCenter(screenCenter.x, screenCenter.y);
			gameEngine->setHeaderPosition(screenCenter);
		}
		window.setView(camera);
	}
	
}


void Level1::checkEnd() {
	Vector2f marioPos = gameEngine->mario.marioSprite.getPosition();
	int space = 70;
	if (marioPos.x < space){
		gameEngine->mario.marioSprite.setPosition(space, marioPos.y);
		gameEngine->mario.speed[0] = 0;
	}
	else if (marioPos.x > levelWidth - space) {
		gameEngine->mario.marioSprite.setPosition(levelWidth - space, marioPos.y);
		gameEngine->mario.speed[0] = 0;
	}
}