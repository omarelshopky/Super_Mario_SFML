#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Items.h"
#include "../Header/Blocks.h"	

#define COINS_NUM 1
#define FLOWERS_NUM 1
#define MASHROOMS_NUM 1
#define STONE_NUM 1
#define QUESTION_NUM 2

class Level1
{
	/***			Properties				***/
private:
	vector<Items> coin, flower, mashroom;
	vector<Blocks> stone, question;
	GameEngine* gameEngine;
	position coinPosition[COINS_NUM], flowerPosition[FLOWERS_NUM], mashroomPosition[MASHROOMS_NUM],
		stonePostition[STONE_NUM], questionPosition[QUESTION_NUM];
	bool display, marioOnGround;
	Texture backGroundTexture, groundTexture;
	RectangleShape backGroundShape, groundShape;
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
	void checkGround();
};

