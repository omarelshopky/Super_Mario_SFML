#include "../Header/Level1.h"


Level1::Level1(GameEngine& gameEngine) {
	// Set initial values
	this->gameEngine = &gameEngine;
	display = false;
	memset(marioOnGround, false, sizeof marioOnGround);
	stoneCnt = rockCnt = quesCnt = coinCnt = 0;
	levelWidth = 13397;
	
		
	// Set Positions
	arrangeLevelBlocks();
	
	gameEngine.setLevelName("Level 1");

	// Call Constructer for all coins 
	for (int i = 0; i < coinCnt; i++) {
		coin.push_back(*new Items(gameEngine, COIN, coinPosition[i].x, coinPosition[i].y));
	}

	// Call Constructer for all Stone Blocks
	for (int i = 0; i < stoneCnt; i++) {
		stone.push_back(*new Blocks(gameEngine, STONE, COIN, stonePosition[i].x, stonePosition[i].y));
		stone[i].blockSprite.setColor(Color::Color(70, 50, 180)); // Blue filter
	}

	// Call Constructer for all Rock Blocks
	for (int i = 0; i < rockCnt; i++) {
		rock.push_back(*new Blocks(gameEngine, ROCK, COIN, rockPosition[i].x, rockPosition[i].y));
		rock[i].blockSprite.setColor(Color::Color(70, 50, 180)); // blue filter
	}

	// Call Constructer for all Question Blocks
	for (int i = 0; i < quesCnt; i++) {
		question.push_back(*new Blocks(gameEngine, QUESTION, COIN, questionPosition[i].x, questionPosition[i].y));
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
		for (int i = 0; i < coinCnt; i++) 
			coin[i].draw(window);

		for (int i = 0; i < stoneCnt; i++)
			stone[i].draw(window);

		for (int i = 0; i < rockCnt; i++)
			rock[i].draw(window);

		for (int i = 0; i < quesCnt; i++)
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
	//if (!gameEngine->mario.stuck) { 
		position screenCenter = { gameEngine->mario.marioSprite.getPosition().x, 450 };

		if (screenCenter.x > WINDOW_WIDTH / 2 && screenCenter.x < levelWidth - (WINDOW_WIDTH / 2)) {
			camera.setCenter(screenCenter.x, screenCenter.y);
			gameEngine->setHeaderPosition(screenCenter);
		}
		window.setView(camera);
	//}
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


//void Level1::setCoinPosition() {
//	coinPosition[0] = { 1280,288 }, coinPosition[1] = { 1322, 192 }, coinPosition[2] = { 1364, 192 },
//		coinPosition[3] = { 1406, 192 }, coinPosition[4] = { 1448, 288 }, coinPosition[5] = { 1408, 192 },
//		coinPosition[6] = { 1856, 256 }, coinPosition[7] = { 1888, 256 }, coinPosition[8] = { 1920, 256 },
//		coinPosition[9] = { 1952, 256 }, coinPosition[10] = { 2688, 160 }, coinPosition[11] = { 2720, 160 },
//		coinPosition[12] = { 2752, 160 }, coinPosition[13] = { 2784, 160 }, coinPosition[14] = { 2816, 160 },
//		coinPosition[15] = { 2284, 160 };
//}

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


void Level1::arrangeLevelBlocks() {
	float arr[13][300] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,80,0,0,80,0,0,0,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
		{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,80,0,0,80,0,0,0,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,80,0,0,80,0,0,0,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,80,0,0,80,0,0,0,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,80,0,0,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,9,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,80,0,0,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,80,0,0,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0,0,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,80,0,0,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{10,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,10,10,10,10,10,10,10,10,10,10,10,10,10,9,10,10,10,10,10,10,10,10,10,10,10,9,0,0,0,0,0,0,0,0,0,0,0,0,80,0,0,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,81,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,0,80,0,0,80,0,0,9,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,10,0,0,10,10,10,0,0,10,10,10,0,0,10,10,0,0,10,10,10,10,10,10,10,0,0,0,10,10,10,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,0,80,0,0,80,0,0,10,10,10,10,10,10,10,10,10,0,0,0,0,9,0,0,0,0,10,0,0,10,10,10,0,0,10,10,10,0,0,10,10,0,0,10,10,10,10,10,10,10,0,0,0,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25},
		{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,0,80,0,0,80,0,0,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,10,0,0,10,10,10,0,0,10,10,10,0,0,10,10,0,0,10,10,10,10,10,10,10,0,0,0,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25}
	};

	for (int i = 0; i < 13; i++) row[i] = 31 + i * 62;

	for (int i = 0; i < 300; i++) col[i] = 31 + i * 62;

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 300; j++) {
			if (arr[i][j] != 0) {
				stonePosition[stoneCnt] = { col[j],  row[i] };
				stoneCnt++;
			}
			else if (arr[i][j] == 2){
				rockPosition[rockCnt] = { col[j],  row[i] };
				rockCnt++;
			}else if(arr[i][j] == 3){
				questionPosition[quesCnt] = { col[j],  row[i] };
				quesCnt++;
			}
			else if (arr[i][j] == 4) {
				coinPosition[coinCnt] = { col[j],  row[i] };
				coinCnt++;
			}
		}
	}
}