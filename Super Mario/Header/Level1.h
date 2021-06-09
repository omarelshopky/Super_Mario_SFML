#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Items.h"
#include "../Header/Blocks.h"	

#define COINS_NUM 1500
#define STONE_NUM 1500
#define ROCK_NUM 1500
#define QUESTION_NUM 1500
#define GROUNDS_NUM 6

class Level1
{
	/***			Properties				***/
private:
	vector<Items> coin;
	vector<Blocks> stone, question, rock;
	GameEngine* gameEngine;
	position coinPosition[COINS_NUM], stonePosition[STONE_NUM], questionPosition[QUESTION_NUM], rockPosition[ROCK_NUM];
	bool display, marioOnGround[GROUNDS_NUM];
	float levelWidth, row[14], col[300];
	int stoneCnt, rockCnt, quesCnt, coinCnt;
	Texture backGroundTexture, groundTexture;
	RectangleShape backGroundShape, groundShape[GROUNDS_NUM];
	View camera;
	
public:
	Level1(GameEngine& gameEngine);


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

