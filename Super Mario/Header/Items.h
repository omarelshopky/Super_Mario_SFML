#pragma once
#include "../Header/DEFINITION.h"

class Items
{
private:
	/***			Properties				***/
	Texture itemTexture;
	Sprite itemSprite;
	IntRect itemIntRect, coinIntRect, flowerIntRect, mashroomIntRect, sparklsIntRect;
	Clock timer;
	int CurrentRect, maxRect;
	bool display, faid;

public:
	item_t itemType;

	/***			Constructor 			***/
	Items(item_t item, float x, float y);


	/***			Methods				***/

	// Draw item on screen
	void draw(RenderWindow& window);

private:
	// handle animation for the item
	void animation();
};

