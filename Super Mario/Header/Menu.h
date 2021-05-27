#pragma once

#include <SFML/Graphics.hpp>
#include "../Header/DEFINITION.h"
using namespace sf;

#define NUM_OF_OPTIONS 6

class Menu
{
	// Menu properties
private:
	int selectedOption;
	Font menuFont, playerNameFont;
	Text menuOptions[NUM_OF_OPTIONS];
	Texture optionShadowTexture, backGroundTexture, playerNameTexture;
	Sprite optionShadowSprite, backGroundSprite, playerNameSprite;
	String playerNameStr;
	Text playerNameText;
	bool mainMenuDisplay, playerNameDisplay, levelsListDisplay;

public:
	std::string playerName;

	// Constractor
	Menu(); 


	// Draw Menu Options
	void draw(RenderWindow& window);


	// Control Menu events
	void catchEvents(Event& event, RenderWindow& window);


	

private:
	// Move up to the previous option
	void moveUp();


	// Move to the next option
	void moveDown();


	// Make player name menu display
	void openPlayerName();


	// Handle what would done when chose specific option
	void mainMenuHandleSelection();
};