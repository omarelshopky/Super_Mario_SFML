#include "../Header/Level1.h"


Level1::Level1(GameEngine& gameEngine) {
	// Set initial values
	this->gameEngine = &gameEngine;
	display = false;
	memset(marioOnGround, false, sizeof marioOnGround);
	levelWidth = 13397;
	row[0] = 31, row[1] = 93, row[2] = 155, row[3] = 217, row[4] = 279, row[5] = 341, row[6] = 403,
		row[7] = 465, row[8] = 527, row[9] = 589, row[10] = 651, row[11] = 713, row[12] = 775;

	// Set Positions
	setStonesPosition();
	setRocksPosition();
	setQuestionPosition();
	setCoinPosition();
	
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
	setGroundProperties();

	// Set View Properites
	camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	camera.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}


void Level1::draw(RenderWindow& window) {
	if (display) {
		window.draw(backGroundShape);

		for (int i = 0; i < GROUNDS_NUM; i++) {
			checkGround(i);
			window.draw(groundShape[i]);
		}
		
		checkEnd();
		handleView(window);
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


void Level1::checkGround(int num){
	if (!gameEngine->mario.dying) {
		if (groundShape[num].getGlobalBounds().intersects(gameEngine->mario.marioSprite.getGlobalBounds())) {
			gameEngine->mario.marioSprite.setPosition(gameEngine->mario.marioSprite.getPosition().x, groundShape[num].getGlobalBounds().top);
			gameEngine->mario.onGround = true;
			marioOnGround[num] = true;
		}
		else {
			if (marioOnGround[num] && gameEngine->mario.onGround) {
				marioOnGround[num] = false;
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
	stonePosition[0] = { 31, row[0] }, stonePosition[1] = { 13299, row[0] }, stonePosition[2] = { 13361,row[0] };
	
	// Row 2
	stonePosition[187] = { 31, row[1] }, stonePosition[188] = { 3379,row[1] }, stonePosition[189] = { 3441,row[1] };
	fillSequence(stonePosition, 6, 190, 3627, row[1]);
	fillSequence(stonePosition, 4, 196, 4123, row[1]);
	fillSequence(stonePosition, 5, 200, 4743, row[1]);
	fillSequence(stonePosition, 33, 205, 10447, row[1]);
	fillSequence(stonePosition, 2, 238, 13299, row[1]);
	
	// Row 3
	stonePosition[240] = { 31, row[2] };
	fillSequence(stonePosition, 2, 241, 3379, row[2]);
	fillSequence(stonePosition, 6, 243, 3627, row[2]);
	fillSequence(stonePosition, 4, 249, 4123, row[2]);
	fillSequence(stonePosition, 5, 253, 4743, row[2]);
	fillSequence(stonePosition, 33, 258, 10447, row[2]);
	fillSequence(stonePosition, 2, 291, 13299, row[2]);

	// Row 4
	stonePosition[293] = { 31, row[3] };
	fillSequence(stonePosition, 2, 294, 3255, row[3]);
	fillSequence(stonePosition, 2, 296, 3875, row[3]);
	stonePosition[298] = { 4185, row[3] };
	fillSequence(stonePosition, 2, 299, 4495, row[3]);
	fillSequence(stonePosition, 33, 301, 10447, row[3]);
	fillSequence(stonePosition, 2, 334, 13299, row[3]);

	// Row 5
	stonePosition[336] = { 31, row[4] };
	fillSequence(stonePosition, 2, 337, 3255, row[4]);
	fillSequence(stonePosition, 2, 339, 3875, row[4]);
	stonePosition[401] = { 4185, row[4] };
	fillSequence(stonePosition, 2, 402, 4495, row[4]);
	fillSequence(stonePosition, 33, 404, 10447, row[4]);
	fillSequence(stonePosition, 2, 437, 13299, row[4]);

	// Row 6
	stonePosition[439] = { 31, row[5] };
	fillSequence(stonePosition, 2, 440, 3255, row[5]);
	fillSequence(stonePosition, 2, 442, 3875, row[5]);
	stonePosition[446] = { 4185, row[5] };
	fillSequence(stonePosition, 2, 447, 4495, row[5]);
	fillSequence(stonePosition, 6, 449, 5239, row[5]);
	fillSequence(stonePosition, 33, 455, 10447, row[5]);
	fillSequence(stonePosition, 2, 488, 13299, row[5]);

	// Row 7
	stonePosition[490] = { 31, row[6] }, stonePosition[491] = { 2449, row[6] };
	fillSequence(stonePosition, 4, 492, 2573, row[6]);
	stonePosition[496] = { 2883, row[6] };
	fillSequence(stonePosition, 2, 497, 3255, row[6]);
	fillSequence(stonePosition, 2, 499, 3875, row[6]);
	stonePosition[501] = { 4185, row[6] }, stonePosition[502] = { 4309, row[6] };
	fillSequence(stonePosition, 2, 503, 4495, row[6]);
	fillSequence(stonePosition, 6, 505, 5239, row[6]);
	fillSequence(stonePosition, 33, 511, 10447, row[6]);
	fillSequence(stonePosition, 2, 544, 13299, row[6]);

	// Row 8
	stonePosition[546] = { 31, row[7] }, stonePosition[547] = { 1829, row[7] }, stonePosition[548] = { 2449, row[7] },
		stonePosition[549] = { 2573, row[7] }, stonePosition[550] = { 2759, row[7] }, stonePosition[551] = { 2883, row[7] };
	fillSequence(stonePosition, 4, 552, 3255, row[7]);
	fillSequence(stonePosition, 6, 556, 3627, row[7]);
	fillSequence(stonePosition, 3, 562, 4185, row[7]);
	fillSequence(stonePosition, 2, 565, 4495, row[7]);
	fillSequence(stonePosition, 5, 567, 4743, row[7]);
	fillSequence(stonePosition, 6, 572, 9021, row[7]);
	fillSequence(stonePosition, 35, 578, 10323, row[7]);
	fillSequence(stonePosition, 2, 613, 13299, row[7]);

	// Row 9
	stonePosition[615] = { 31 , row[8] };
	fillSequence(stonePosition, 3, 616, 2449, row[8]);
	fillSequence(stonePosition, 3, 619, 2759, row[8]);
	fillSequence(stonePosition, 2, 622, 3379, row[8]);
	fillSequence(stonePosition, 35, 624, 10323, row[8]);
	fillSequence(stonePosition, 2, 659, 13299, row[8]);

	// Row 10
	stonePosition[661] = { 31, row[9] };
	fillSequence(stonePosition, 2, 662, 3379, row[9]);
	fillSequence(stonePosition, 2, 664, 7595, row[9]);
	fillSequence(stonePosition, 41, 666, 9951, row[9]);
	fillSequence(stonePosition, 2, 707, 13299, row[9]);

	// Row 11
	stonePosition[709] = { 31, row[10] };
	fillSequence(stonePosition, 2, 710, 3379, row[10]);
	fillSequence(stonePosition, 2, 712, 7595, row[10]);
	fillSequence(stonePosition, 41, 714, 9951, row[10]);
	fillSequence(stonePosition, 2, 755, 13299, row[10]);

	stonePosition[757] = { 31, row[11] }; // Row 12

	stonePosition[758] = { 31, row[12] }; // Row 13
}


void Level1::setRocksPosition() {
	// Row 9
	rockPosition[0] = { 1457, row[8] }, rockPosition[1] = { 1581, row[8] };
	fillSequence(rockPosition, 2, 2, 8463, row[8]);
	// Row 10
	rockPosition[4] = { 1333, row[9] }, rockPosition[5] = { 1457, row[9] }, rockPosition[6] = { 1581, row[9] },
		rockPosition[7] = { 1705, row[9] }, rockPosition[8] = { 1953, row[9] };
	fillSequence(rockPosition, 3, 9, 8401, row[9]);
	// Row 11
	rockPosition[12] = { 1209, row[10] }, rockPosition[13] = { 1333, row[10] }, rockPosition[14] = { 1457, row[10] },
		rockPosition[15] = { 1581, row[10] }, rockPosition[16] = { 1705, row[10] }, rockPosition[17] = { 1953, row[10] },
		rockPosition[18] = { 2077, row[10] };
	fillSequence(rockPosition, 4, 19, 8339, row[10]);
	// Row 12
	rockPosition[23] = { 1085, row[11] }, rockPosition[24] = { 1209, row[11] }, rockPosition[25] = { 1333, row[11] },
		rockPosition[26] = { 1457, row[11] }, rockPosition[27] = { 1581, row[11] }, rockPosition[28] = { 1705, row[11] },
		rockPosition[29] = { 1953, row[11] }, rockPosition[30] = { 2077, row[11] };
	// Row 13
	rockPosition[31] = { 1085, row[12] }, rockPosition[32] = { 1209, row[12] }, rockPosition[33] = { 1333, row[12] };
	fillSequence(rockPosition, 3, 34, 1457, row[12]);
	rockPosition[37] = { 1705, row[12] }, rockPosition[38] = { 1953, row[12] }, rockPosition[39] = { 2077, row[12] };
}


void Level1::setQuestionPosition() {
	// Row 9
	fillSequence(questionPosition, 5, 0, 651, row[8]);
	// Row 10
	fillSequence(questionPosition, 2, 5, 6789, row[9]);
	fillSequence(questionPosition, 2, 7, 12555, row[9]);
	fillSequence(questionPosition, 2, 9, 12803, row[9]);
	fillSequence(questionPosition, 2, 11, 13051, row[9]);
	// Row 11
	fillSequence(questionPosition, 2, 13, 6417, row[10]);
	questionPosition[15] = { 6727, row[10] }, questionPosition[16] = { 6913, row[10] };
	fillSequence(questionPosition, 2, 17, 7161, row[10]);
}

void Level1::setCoinPosition() {
	coinPosition[0] = { 1280,288 }, coinPosition[1] = { 1322, 192 }, coinPosition[2] = { 1364, 192 },
		coinPosition[3] = { 1406, 192 }, coinPosition[4] = { 1448, 288 }, coinPosition[5] = { 1408, 192 },
		coinPosition[6] = { 1856, 256 }, coinPosition[7] = { 1888, 256 }, coinPosition[8] = { 1920, 256 },
		coinPosition[9] = { 1952, 256 }, coinPosition[10] = { 2688, 160 }, coinPosition[11] = { 2720, 160 },
		coinPosition[12] = { 2752, 160 }, coinPosition[13] = { 2784, 160 }, coinPosition[14] = { 2816, 160 },
		coinPosition[15] = { 2284, 160 };
}

void Level1::setGroundProperties() {
	for (int i = 0; i < GROUNDS_NUM; i++) groundShape[i].setTexture(&groundTexture);

	groundShape[0].setSize(Vector2f(5022, 140));
	groundShape[0].setPosition(0, 806);

	groundShape[1].setSize(Vector2f(2232, 140));
	groundShape[1].setPosition(5208, 806);

	groundShape[2].setSize(Vector2f(124, 140));
	groundShape[2].setPosition(7564, 806);

	groundShape[3].setSize(Vector2f(744, 140));
	groundShape[3].setPosition(7812, 806);

	groundShape[4].setSize(Vector2f(496, 140));
	groundShape[4].setPosition(8990, 806);

	groundShape[5].setSize(Vector2f(3472, 140));
	groundShape[5].setPosition(9920, 806);
}