#include "../Header/Items.h"

Items::Items(item_t item, float x, float y) {
	// Set initial values
	display = true;
	faid = false;
	CurrentRect = floatingSpeed =  0;
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
	itemSprite.setOrigin(itemIntRect.width / 2, itemIntRect.height / 2);

	// Set Floating text properties
	font.loadFromFile(FLOATING_FONT);
	floatingText.setFont(font);
	floatingText.setCharacterSize(18);
	floatingText.setStyle(Text::Bold);
	floatingText.setOrigin(9, 9);
	floatingText.setPosition(x, y);
	floatingText.setLetterSpacing(0.01);
	floatingText.setFillColor(Color(218, 18, 29));
	floatingText.setString("100");
}


void Items::draw(RenderWindow& window) {
	animation();
	if (display) {
		if(faid) window.draw(floatingText);
		window.draw(itemSprite);
	}
}


void Items::animation() {
	if (timer.getElapsedTime().asSeconds() > 0.2f) {
		switch (itemType) {
		case COIN:
			itemIntRect.left = coinIntRect.left + CurrentRect * coinIntRect.width;
			break;
		case FLOWER:
			itemIntRect.left = flowerIntRect.left + CurrentRect * flowerIntRect.width;
			break;
		case MASHROOM:
			itemIntRect.left = mashroomIntRect.left + CurrentRect * mashroomIntRect.width;
			break;
		case SPARKL:
			if (!faid) {
				maxRect = 6;
				CurrentRect = 0;
				itemIntRect = sparklsIntRect;
				faid = true;
			}
			else {
				itemIntRect.left = sparklsIntRect.left + CurrentRect * sparklsIntRect.width;
				if (CurrentRect == maxRect - 1) display = false;
			}
		}
		itemSprite.setTextureRect(itemIntRect);
		CurrentRect++;

		if (CurrentRect == maxRect) CurrentRect = 0;

		timer.restart();
	}
	TextFloat();
}


void Items::startTextFloat() {
	itemType = SPARKL;
	textFloatTimer.restart();
}


void Items::TextFloat() {
	if (faid) {
		int currentTime = textFloatTimer.getElapsedTime().asMilliseconds();
		if (currentTime < 130)//375
		{
			floatingSpeed += -1;
		}
		else if (currentTime < 750)//750
		{
			floatingText.setFillColor(Color(219, 59, 78));
			floatingSpeed += -0.1;
		}
		else if (currentTime < 1100)
		{
			floatingText.setFillColor(Color(179, 116, 146));
			floatingSpeed += -0.1;
		}
		else
		{
			floatingText.setFillColor(Color::Transparent);
			floatingSpeed = 0; //Reseting its value
		}
		floatingText.move(0, floatingSpeed);
	}
}