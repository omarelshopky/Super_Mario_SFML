#include "../Header/CreditsMenu.h"

CreditsMenu::CreditsMenu() {
	display = false;

	// Set Back Text Properties
	setBackText();

	// Load background
	if (!backGroundTexture.loadFromFile(CREDITS_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);
}