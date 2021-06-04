#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Items.h"


#define COINS_NUM 1
#define FLOWERS_NUM 1
#define MASHROOMS_NUM 1

class Level1
{
	/***			Properties				***/
private:
	vector<Items> coin;
	vector<Items> flower;
	vector<Items> mashroom;
	GameEngine* gameEngine;
	position coinPosition[COINS_NUM], flowerPosition[FLOWERS_NUM], mashroomPosition[MASHROOMS_NUM];
	bool display;
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
};

