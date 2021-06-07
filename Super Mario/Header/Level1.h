#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Items.h"
#include "../Header/Blocks.h"	

#define COINS_NUM 16
#define STONE_NUM 232
#define ROCK_NUM 1
#define QUESTION_NUM 1

class Level1
{
	/***			Properties				***/
private:
	vector<Items> coin;
	vector<Blocks> stone, question, rock;
	GameEngine* gameEngine;
	position coinPosition[COINS_NUM], stonePosition[STONE_NUM], questionPosition[QUESTION_NUM], rockPosition[ROCK_NUM];
	bool display, marioOnGround;
	float levelWidth;
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


	// Set Camera View with mario movement
	void handleView(RenderWindow& window);


	// Check end of the level
	void checkEnd();

private:
	// Arrange Array for Stone Blocks position on screen
	void setStonesPosition();

	void fillSequence(position arr[], int numOfThings, int firstIndex, float startingPos, float yPosition);
};

