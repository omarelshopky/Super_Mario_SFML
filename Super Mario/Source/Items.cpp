#include "../Header/Items.h"

Items::Items(item_t item, float x, float y) {
	// Set initial values
	display = true;
	faid = false;
	CurrentRect = 0;
	itemType = item;
	coinIntRect = IntRect(0, 86, 33, 30);
	flowerIntRect = IntRect(32, 213, 32, 30);
	mashroomIntRect = IntRect(128, 150, 32.5, 45);
	sparklsIntRect = IntRect(0, 116, 40, 32);

	// Set item Sprite properties
	itemTexture.loadFromFile(ITEMS);
	itemSprite.setTexture(itemTexture);
	itemSprite.setPosition(x, y);
	itemSprite.setScale(1.5, 1.5);

	switch (itemType) {
	case COIN:
		itemIntRect = coinIntRect;
		maxRect = 4;
		break;
	case FLOWER:
		itemIntRect = flowerIntRect;
		maxRect = 3;
		break;
	case MASHROOM:
		itemIntRect = mashroomIntRect;
		maxRect = 2;
		break;
	}

	itemSprite.setTextureRect(itemIntRect);
}


void Items::draw(RenderWindow& window) {
	animation();
	if(display)	window.draw(itemSprite);
}






void Items::animation() {
	if (timer.getElapsedTime().asSeconds() > 0.2f) {
		switch (itemType) {
		case COIN:
			itemIntRect.left = coinIntRect.left + CurrentRect * 33;
			break;
		case FLOWER:
			itemIntRect.left = flowerIntRect.left + CurrentRect * 32;
			break;
		case MASHROOM:
			itemIntRect.left = mashroomIntRect.left + CurrentRect * 32.5;
			break;
		case SPARKL:
			if (!faid) {
				maxRect = 6;
				CurrentRect = 0;
				itemIntRect = sparklsIntRect;
				faid = true;
			}
			else {
				itemIntRect.left = sparklsIntRect.left + CurrentRect * 40;
				if (CurrentRect == maxRect - 1) display = false;
			}
		}
		itemSprite.setTextureRect(itemIntRect);
		CurrentRect++;

		if (CurrentRect == maxRect) CurrentRect = 0;

		timer.restart();
	}
}

