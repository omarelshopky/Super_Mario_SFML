#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/GameEngine.h"
#include "../Header/Items.h"

class Blocks{
private:
	/***			Properties				***/
	IntRect blockRect, stoneRect, questionRect, bronzeRect, smashRect, rockRect;
	Clock timer, popUpTimer;
	int currentRect, maxRect, movingSpeed;
	bool display, faid, isPopUp, marioOn, stuckOn, popUpBlock;
	position startPos;
	block_t blockType;
	item_t	itemType;
	GameEngine* gameEngine;
	Items item;

public:
	Sprite blockSprite;

	Blocks(GameEngine& gameEngine, block_t blockType, item_t itemType, float x, float y); // Constructer
	

	/***			Methods				***/

	// Draw item on screen
	void draw(RenderWindow& window);


	// start animation of poping up
	void startPopUp();


	// Smash stone block then disapear
	void smash();

private:
	// handle animation for the block
	void animation();


	// Block moving up then down.
	void popUp();


	// Check if mario hit this block
	void checkIntersection();


	// Handle what will done when mario hit the block with his head
	void handleHitBlock();
};

