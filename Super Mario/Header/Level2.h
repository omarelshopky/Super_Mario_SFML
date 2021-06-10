#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Blocks.h"	
#include "../Header/Enemy.h"

#define COINS_NUM 1500
#define STONE_NUM 1500
#define STONE_WITH_COIN_NUM 1500
#define QUESTION_WITH_COIN_NUM 1500
#define QUESTION_WITH_MASH_NUM 1500
#define QUESTION_WITH_FLOWER_NUM 1500
#define ROCK_NUM 1500
#define GROUNDS_NUM 6
#define BLACK_NUM 1
#define TURTLE_NUM 1
#define ROW_NUM 14
#define COL_NUM 300

class Level2
{
	/***			Properties				***/
private:
	vector<Items> coin;
	vector<Blocks> stone, question, rock;
	vector<Enemy> black, turtle;
	GameEngine* gameEngine;
	position coinPosition[COINS_NUM], stonePosition[STONE_NUM], stoneCoinPosition[STONE_WITH_COIN_NUM],
		questCoinPosition[QUESTION_WITH_COIN_NUM], questMashPosition[QUESTION_WITH_MASH_NUM],
		questFLowerPosition[QUESTION_WITH_FLOWER_NUM], rockPosition[ROCK_NUM];
	bool display, marioOnGround[GROUNDS_NUM];
	float levelWidth;
	int coinCnt, stoneCnt, stoneCoinCnt, quesCoinCnt, quesMashCnt, quesFlowerCnt, rockCnt;
	Texture backGroundTexture, groundTexture;
	RectangleShape backGroundShape, groundShape[GROUNDS_NUM];
	View camera;
	position screenCenter = { 0, 0 };

public:
	Level2(GameEngine& gameEngine);


	/***			Methods				***/
	// Draw Levels contents
	void draw(RenderWindow& window);


	// Control all level event
	void catchEvents(Event event);


	// Make Level start
	void start();


	// Close Level
	void end();


	// Check weather mario in ground or not
	void checkGround(int num);


	// Set Camera View with mario movement
	void handleView(RenderWindow& window);


	// Check end of the level
	void checkEnd();

private:
	// Arrange Array for Grounds Properties on screen
	void setGroundProperties();


	// Set Positions for all blocks in the level
	void arrangeLevelBlocks();
};

