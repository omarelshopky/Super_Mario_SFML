#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Mario.h"
#include "../Header/GameEngine.h"

class Items
{
private:
	/***			Properties				***/
	GameEngine* gameEngine;
	IntRect itemIntRect, coinIntRect, flowerIntRect, mashroomIntRect, sparklsIntRect;
	Clock timer, textFloatTimer;
	Text floatingText;
	item_t itemType;
	int CurrentRect, maxRect, floatingSpeed, takenScore;
	bool faid, isTaken, resetTime;

public:
	Sprite itemSprite;
	bool display, blockPoped;
	float itemHeight;

	/***			Constructor 			***/
	Items(GameEngine& gameEngine, item_t item, float x, float y);


	/***			Methods				***/

	// Draw item on screen
	void draw(RenderWindow& window);

private:
	// handle animation for the item
	void animation();


	// Block moving up then down.
	void TextFloat();


	// Check If mario has taken this item or not
	void checkTaken();


	// Handle what will happend when item is taken
	void setTaken();
};

