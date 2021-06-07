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
		stone.push_back(*new Blocks(gameEngine.mario, gameEngine, STONE, stonePosition[i].x, stonePosition[i].y));
		stone[i].blockSprite.setColor(Color::Color(70, 50, 180)); // Blue filter
	}

	// Call Constructer for all Rock Blocks
	for (int i = 0; i < ROCK_NUM; i++) {
		rock.push_back(*new Blocks(gameEngine.mario, gameEngine, ROCK, rockPosition[i].x, rockPosition[i].y));
		rock[i].blockSprite.setColor(Color::Color(70, 50, 180)); // blue filter
	}

	// Call Constructer for all Question Blocks
	for (int i = 0; i < QUESTION_NUM; i++) {
		question.push_back(*new Blocks(gameEngine.mario, gameEngine, QUESTION, questionPosition[i].x, questionPosition[i].y));
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
	float y1 = 31; // Row 1
	stonePosition[0] = { 31, y1 }, stonePosition[1] = { 13299, y1 }, stonePosition[2] = { 13361,y1 };
	
	float y2 = 93; // Row 2
	stonePosition[3] = { 31, y2 };
	fillSequence(stonePosition, 131, 4, 465, y2);
	fillSequence(stonePosition, 50, 135, 10013, y2);
	stonePosition[185] = { 13299, y2 }, stonePosition[186] = { 13361,y2 };
	
	float y3 = 155; // Row 3
	stonePosition[187] = { 31, y3 }, stonePosition[188] = { 3379,y3 }, stonePosition[189] = { 3441,y3 };
	fillSequence(stonePosition, 6, 190, 3627, y3);
	fillSequence(stonePosition, 4, 196, 4123, y3);
	fillSequence(stonePosition, 5, 200, 4743, y3);
	fillSequence(stonePosition, 33, 205, 10447, y3);
	fillSequence(stonePosition, 2, 238, 13299, y3);

	float y4 = 217; // Row 4
	stonePosition[240] = { 31, y4 };
	fillSequence(stonePosition, 2, 241, 3379, y4);
	fillSequence(stonePosition, 6, 243, 3627, y4);
	fillSequence(stonePosition, 4, 249, 4123, y4);
	fillSequence(stonePosition, 5, 253, 4743, y4);
	fillSequence(stonePosition, 33, 258, 10447, y4);
	fillSequence(stonePosition, 2, 291, 13299, y4);

	float y5 = 279; // Row 5
	stonePosition[293] = { 31, y5 };
	fillSequence(stonePosition, 2, 294, 3255, y5);
	fillSequence(stonePosition, 2, 296, 3875, y5);
	stonePosition[298] = { 4185, y5 };
	fillSequence(stonePosition, 2, 299, 4495, y5);
	fillSequence(stonePosition, 33, 301, 10447, y5);
	fillSequence(stonePosition, 2, 334, 13299, y5);

	float y6 = 341; // Row 6
	stonePosition[336] = { 31, y6 };
	fillSequence(stonePosition, 2, 337, 3255, y6);
	fillSequence(stonePosition, 2, 339, 3875, y6);
	stonePosition[401] = { 4185, y6 };
	fillSequence(stonePosition, 2, 402, 4495, y6);
	fillSequence(stonePosition, 33, 404, 10447, y6);
	fillSequence(stonePosition, 2, 437, 13299, y6);

	float y7 = 403; // Row 7
	stonePosition[439] = { 31, 403 };
	fillSequence(stonePosition, 2, 440, 3255, y7);
	fillSequence(stonePosition, 2, 442, 3875, y7);
	stonePosition[446] = { 4185, y7 };
	fillSequence(stonePosition, 2, 447, 4495, y7);
	fillSequence(stonePosition, 6, 449, 5239, y7);
	fillSequence(stonePosition, 33, 455, 10447, y7);
	fillSequence(stonePosition, 2, 488, 13299, y7);

	float y8 = 465; // Row 8
	stonePosition[490] = { 31, y8 }, stonePosition[491] = { 2449, y8 };
	fillSequence(stonePosition, 4, 492, 2573, y8);
	stonePosition[496] = { 2883, y8 };
	fillSequence(stonePosition, 2, 497, 3255, y8);
	fillSequence(stonePosition, 2, 499, 3875, y8);
	stonePosition[501] = { 4185, y8 }, stonePosition[502] = { 4309, y8 };
	fillSequence(stonePosition, 2, 503, 4495, y8);
	fillSequence(stonePosition, 6, 505, 5239, y8);
	fillSequence(stonePosition, 33, 511, 10447, y8);
	fillSequence(stonePosition, 2, 544, 13299, y8);

	float y9 = 527; // Row 9
	stonePosition[546] = { 31, y9 }, stonePosition[547] = { 1829, y9 }, stonePosition[548] = { 2449, y9 },
		stonePosition[549] = { 2573, y9 }, stonePosition[550] = { 2759, y9 }, stonePosition[551] = { 2883, y9 };
	fillSequence(stonePosition, 4, 552, 3255, y9);
	fillSequence(stonePosition, 6, 556, 3627, y9);
	fillSequence(stonePosition, 3, 562, 4185, y9);
	fillSequence(stonePosition, 2, 565, 4495, y9);
	fillSequence(stonePosition, 5, 567, 4743, y9);
	fillSequence(stonePosition, 6, 572, 9021, y9);
	fillSequence(stonePosition, 35, 578, 10323, y9);
	fillSequence(stonePosition, 2, 613, 13299, y9);

	/*   stonePosition[9] = { 31,589 }, stonePosition[10] = { 31, 651 }, stonePosition[11] = { 31, 713 },
	stonePosition[12] = { 465, 93 }, stonePosition[13] = { 527,93 }, stonePosition[14] = { 589,93 },
	stonePosition[15] = { 651,93 };*/
}