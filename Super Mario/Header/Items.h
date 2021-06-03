#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Mario.h"

class Items
{
private:
	/***			Properties				***/
	Mario *mario;
	Texture itemTexture;
	Sprite itemSprite;
	IntRect itemIntRect, coinIntRect, flowerIntRect, mashroomIntRect, sparklsIntRect;
	Clock timer, textFloatTimer;
	Text floatingText;
	Font font;
	SoundBuffer takenSoundBuffer;
	Sound takenSound;
	item_t itemType;
	int CurrentRect, maxRect, floatingSpeed;
	bool display, faid, isTaken, resetTime;

public:

	/***			Constructor 			***/
	Items(Mario& mario, item_t item, float x, float y);


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

