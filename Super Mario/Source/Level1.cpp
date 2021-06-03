#include "../Header/Level1.h"


Level1::Level1() {
	// Set initial values
	display = false;

	// Set Level's Background Properties
	backGroundTexture.loadFromFile(LEVEL1_BACKGROUND);
	backGroundSprite.setTexture(backGroundTexture);
}

