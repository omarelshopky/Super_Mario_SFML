#include "../Header/Level1.h"


Level1::Level1(GameEngine& gameEngine) {
	// Set initial values
	this->gameEngine = &gameEngine;
	display = marioOnGround = false;
	levelWidth = 13397;

	// Coins Position
	coinPosition[0] = { 1280,288 }, coinPosition[1] = { 1322, 192 }, coinPosition[2] = { 1364, 192 },
		coinPosition[3] = { 1406, 192 }, coinPosition[4] = { 1448, 288 }, coinPosition[5] = { 1408, 192 },
		coinPosition[6] = { 1856, 256 }, coinPosition[7] = { 1888, 256 }, coinPosition[8] = { 1920, 256 },
		coinPosition[9] = { 1952, 256 }, coinPosition[10] = { 2688, 160 }, coinPosition[11] = { 2720, 160 },
		coinPosition[12] = { 2752, 160 }, coinPosition[13] = { 2784, 160 }, coinPosition[14] = { 2816, 160 },
		coinPosition[15] = { 2284, 160 };

	// Stones Position
	setStonesPosition();

	// Rock Position
	rockPosition[0] = { 500, 550 };

	// Question Position
	questionPosition[0] = { 589, 527 };

	gameEngine.setLevelName("Level 1");

	// Call Constructer for all coins 
	for (int i = 0; i < COINS_NUM; i++) {
		coin.push_back(*new Items(gameEngine.mario, gameEngine, COIN, coinPosition[i].x, coinPosition[i].y));
	}

	// Call Constructer for all Stone Blocks
	for (int i = 0; i < STONE_NUM; i++) {
		stone.push_back(*new Blocks(gameEngine.mario, STONE, stonePosition[i].x, stonePosition[i].y));
		stone[i].blockSprite.setColor(Color::Color(70, 50, 180)); // Blue filter
	}

	// Call Constructer for all Rock Blocks
	for (int i = 0; i < ROCK_NUM; i++) {
		rock.push_back(*new Blocks(gameEngine.mario, ROCK, rockPosition[i].x, rockPosition[i].y));
		rock[i].blockSprite.setColor(Color::Color(70, 50, 180)); // blue filter
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
	groundShape.setSize(Vector2f(levelWidth, 156));
	groundShape.setPosition(0, 744);

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
		for (int i = 0; i < COINS_NUM; i++) 
			coin[i].draw(window);

		for (int i = 0; i < STONE_NUM; i++)
			stone[i].draw(window);

		for (int i = 0; i < ROCK_NUM; i++)
			rock[i].draw(window);

		for (int i = 0; i < QUESTION_NUM; i++)
			question[i].draw(window);

		gameEngine->mario.draw(window);
		gameEngine->draw(window);
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

void Level1::fillSequence(position arr[], int numOfThings, int firstIndex, float startingPos, float yPosition) {
	for (int i = 0; i < numOfThings; i++) arr[firstIndex + i] = { float(startingPos + i * 62) , yPosition };
}


void Level1::setStonesPosition() {
	// Row 1
	stonePosition[0] = { 31, 31 }, stonePosition[1] = { 13299, 31 }, stonePosition[2] = { 13361,31 };
	
	// Row 2
	stonePosition[3] = { 31, 93 };
	fillSequence(stonePosition, 131, 4, 465, 93); 
	fillSequence(stonePosition, 50, 135, 10013, 93); 
	stonePosition[185] = { 13299, 93 }, stonePosition[186] = { 13361,93 };
	
	// Row 3
	stonePosition[187] = { 31, 155 }, stonePosition[188] = { 3379,155 }, stonePosition[189] = { 3441,155 };
	fillSequence(stonePosition, 6, 190, 3627, 155);
	fillSequence(stonePosition, 4, 196, 4123, 155);
	fillSequence(stonePosition, 5, 200, 4743, 155);
	fillSequence(stonePosition, 33, 196, 10447, 155);
	fillSequence(stonePosition, 2, 229, 13299, 155);

	// Row 4

	/*stonePosition[4] = { 31, 279 }, stonePosition[5] = { 31, 341 },
	stonePosition[6] = { 31, 403 }, stonePosition[7] = { 31, 465 }, stonePosition[8] = { 31, 527 },
	stonePosition[9] = { 31,589 }, stonePosition[10] = { 31, 651 }, stonePosition[11] = { 31, 713 },
	stonePosition[12] = { 465, 93 }, stonePosition[13] = { 527,93 }, stonePosition[14] = { 589,93 },
	stonePosition[15] = { 651,93 };*/
}