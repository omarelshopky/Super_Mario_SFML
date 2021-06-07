#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Mario.h"


class Blocks{
private:
	/***			Properties				***/
	Texture stoneTexture, questionTexture, smashTextures[6];
	IntRect blockRect, stoneRect, questionRect, bronzeRect, smashRect, rockRect;
	Clock timer, popUpTimer;
	int currentRect, maxRect, movingSpeed;
	float stuckRange;
	bool display, faid, isPopUp, marioOn;
	position startPos;
	block_t blockType;
	Mario *mario;
	SoundBuffer popUpBuffer, smashBuffer;
	Sound hitSound;

public:
	Sprite blockSprite;

	Blocks(Mario& mario, block_t type, float x, float y); // Constructer


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

