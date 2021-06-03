#include "../Header/HowToPlayMenu.h"

HowToPlayMenu::HowToPlayMenu() {
	display = false;

	// Set Back Text Properties
	setBackText();

	setChangeOptionSound();

	// Load background
	if (!backGroundTexture.loadFromFile(HOW_TO_PLAY_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);
}