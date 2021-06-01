#pragma once
#include "../Header/DEFINITION.h"


class Blocks{
private:
	/***			Properties				***/
	Texture stoneTexture, questionTexture, smashTextures[6];
	IntRect blockRect, stoneRect, questionRect, bronzeRect, smashRect;
	Sprite blockSprite;
	Clock timer, popUpTimer;
	int currentRect, maxRect, movingSpeed;
	bool display, faid, isPopUp;
	position startPos;
	block_t blockType;

public:


	Blocks(block_t type, float x, float y); // Constructer


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
};

