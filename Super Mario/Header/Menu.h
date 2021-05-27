#pragma once

#include <SFML/Graphics.hpp>

#include "../Header/DEFINITION.h"
using namespace sf;

#define NUM_OF_OPTIONS 6

class Menu
{
	// Menu properties
private:
	int SelectedOption;
	Font MenuFont;
	Text MenuOptions[NUM_OF_OPTIONS];
	Texture OptionShadowTexture, BackGroundTexture;
	Sprite OptionShadowSprite, BackGroundSprite;

public:

	// Constractor
	Menu(); 


	// Draw Menu Options
	void Draw(RenderWindow& window);


	// Geter for get current selected option
	int  GetSelectedOption();


	// Control Menu events
	void CatchEvents(Event& event, RenderWindow& window);

private:
	// Move up to the previous option
	void MoveUp();


	// Move to the next option
	void MoveDown();
};