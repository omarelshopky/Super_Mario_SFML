#include "../Header/Level1.h"


Level1::Level1(GameEngine& gameEngine) {
	// Set initial values
	this->gameEngine = &gameEngine;
	display = finished = false;
	memset(marioOnGround, false, sizeof marioOnGround);
	coinCnt = stoneCnt = stoneCoinCnt = quesCoinCnt = quesMashCnt = quesFlowerCnt = rockCnt = 0;
	levelWidth = 13397;
	
	// Set View Properites
	camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Set Level's Background Properties
	backGroundTexture.loadFromFile(LEVEL1_BACKGROUND);
	backGroundTexture.setRepeated(true);
	backGroundShape.setTexture(&backGroundTexture);
	backGroundShape.setSize(Vector2f(levelWidth, WINDOW_HEIGHT));

	// Set Level's Ground Properties
	groundTexture.loadFromFile(LEVEL1_GROUND);
	setGroundProperties();

	// Set Positions
	arrangeLevelBlocks();
	
	gameEngine.setLevelName("Level 1");

	// Call Constructer for all coins 
	for (int i = 0; i < coinCnt; i++) coin.push_back(*new Items(gameEngine, COIN, coinPosition[i].x, coinPosition[i].y));
		
	// Call Constructer for all Stone Blocks
	for (int i = 0; i < stoneCnt; i++) { // Null
		stone.push_back(*new Blocks(gameEngine, STONE, NONE, stonePosition[i].x, stonePosition[i].y));
		stone[i].blockSprite.setColor(Color::Color(70, 50, 180)); // Blue filter
	}

	for (int i = stoneCnt; i < (stoneCnt + stoneCoinCnt); i++) { // With Coin
		stone.push_back(*new Blocks(gameEngine, STONE, COIN, stoneCoinPosition[i - stoneCnt].x, stoneCoinPosition[i - stoneCnt].y));
		stone[i].blockSprite.setColor(Color::Color(70, 50, 180)); // Blue filter
	}

	// Call Constructer for all Question Blocks
	for (int i = 0; i < quesCoinCnt; i++) // With Coin
		question.push_back(*new Blocks(gameEngine, QUESTION, COIN, questCoinPosition[i].x, questCoinPosition[i].y));
		
	for (int i = quesCoinCnt; i < quesMashCnt + quesCoinCnt; i++) // With Coin
		question.push_back(*new Blocks(gameEngine, QUESTION, MASHROOM, questMashPosition[i - quesCoinCnt].x, questMashPosition[i - quesCoinCnt].y));

	for (int i = quesMashCnt + quesCoinCnt; i < quesFlowerCnt + quesMashCnt + quesCoinCnt; i++) // With Coin
		question.push_back(*new Blocks(gameEngine, QUESTION, FLOWER, questFLowerPosition[i - (quesMashCnt + quesCoinCnt)].x, questFLowerPosition[i - (quesMashCnt + quesCoinCnt)].y));

	// Call Constructer for all Rock Blocks
	for (int i = 0; i < rockCnt; i++) {
		rock.push_back(*new Blocks(gameEngine, ROCK, NONE, rockPosition[i].x, rockPosition[i].y));
		rock[i].blockSprite.setColor(Color::Color(70, 50, 180)); // blue filter
	}

	black.push_back(*new Enemy(gameEngine, BLACK, rock[39].blockSprite, rock[40].blockSprite, groundShape[0], 2500, 200));
	turtle.push_back(*new Enemy(gameEngine, TURTLE, rock[41].blockSprite, rock[42].blockSprite, groundShape[1], 5700, 200));
}


void Level1::draw(RenderWindow& window) {
	if (display) {
		if (gameEngine->mario.dying) {
			camera.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			cout << "omar";
		}
		window.draw(backGroundShape);

		for (int i = 0; i < GROUNDS_NUM; i++) {
			checkGround(i);
			window.draw(groundShape[i]);
		}
		
		checkEnd();
		handleView(window);
		for (int i = 0; i < coinCnt; i++) 
			coin[i].draw(window);

		for (int i = 0; i < (stoneCnt + stoneCoinCnt); i++)
			stone[i].draw(window);

		for (int i = 0; i < rockCnt; i++)
			rock[i].draw(window);

		for (int i = 0; i < quesMashCnt + quesCoinCnt + quesFlowerCnt; i++)
			question[i].draw(window);

		for (int i = 0; i < BLACK_NUM; i++)
			black[i].draw(window);

		for (int i = 0; i < TURTLE_NUM; i++)
			turtle[i].draw(window);

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
	camera.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	gameEngine->lifeScreen = true;
	display = true;
	gameEngine->startCountDown();
}


void Level1::end() {
	display = false;
	gameEngine->currentPlayer.level = 2;
	finished = true;
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
	// a + (b - a) * c
	if (/*!gameEngine->mario.stuck*/ !gameEngine->mario.dying) {
		float fr = (1 / 50.0);
		screenCenter = { screenCenter.x + (gameEngine->mario.marioSprite.getPosition().x - screenCenter.x) * fr * 20, 450 };

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
		gameEngine->addPlayerInfo();
		end();
	}
}


void Level1::setGroundProperties() {
	for (int i = 0; i < GROUNDS_NUM; i++) groundShape[i].setTexture(&groundTexture);

	groundShape[0].setSize(Vector2f(5022, 140));
	groundShape[0].setPosition(0, 806);

	groundShape[1].setSize(Vector2f(2232, 140));
	groundShape[1].setPosition(5208, 806);

	groundShape[2].setSize(Vector2f(124, 140));
	groundShape[2].setPosition(7564, 806);

	groundShape[3].setSize(Vector2f(740, 140));
	groundShape[3].setPosition(7808, 806);

	groundShape[4].setSize(Vector2f(496, 140));
	groundShape[4].setPosition(8990, 806);

	groundShape[5].setSize(Vector2f(3488, 140));
	groundShape[5].setPosition(9900, 806);
}


void Level1::arrangeLevelBlocks() {
	short arr[ROW_NUM][COL_NUM] = {
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,4,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,6,1,1,1,1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,2,2,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,7,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,2,2,2,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,6,2,2,2,2,2,6,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,2,2,0,0,0,2,2,1,2,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,2,2,3,2,0,0,0,0,0,0,0,0,0,6,2,2,2,1,6,0,0,7,7,7,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,2,2,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,2,3,2,0,0,0,0,0,0,2,3,2,0,0,0,0,0,2,4,2,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,6,2,3,2,2,3,2,6,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,6,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	
	for (int i = 0; i < ROW_NUM; i++) {
		for (int j = 0; j < COL_NUM; j++) {
			switch (arr[i][j])
			{
			case 1:
				stoneCoinPosition[stoneCoinCnt] = { float(31 + j * 62) ,  float(31 + i * 62) };
				stoneCoinCnt++;
				break;
			case 2:
				stonePosition[stoneCnt] = { float(31 + j * 62) ,  float(31 + i * 62) };
				stoneCnt++;
				break;
			case 3:
				questCoinPosition[quesCoinCnt] = { float(31 + j * 62) ,  float(31 + i * 62) };
				quesCoinCnt++;
				break;
			case 4:
				questFLowerPosition[quesFlowerCnt] = { float(31 + j * 62) ,  float(31 + i * 62) };
				quesFlowerCnt++;
				break;
			case 5:
				questMashPosition[quesMashCnt] = { float(31 + j * 62) ,  float(31 + i * 62) };
				quesMashCnt++;
				break;
			case 6:
				rockPosition[rockCnt] = { float(31 + j * 62) ,  float(31 + i * 62) };
				rockCnt++;
				break;
			case 7:
				coinPosition[coinCnt] = { float(31 + j * 62) ,  float(31 + i * 62) };
				coinCnt++;
				break;
			default:
				break;
			}
		}
	}
}