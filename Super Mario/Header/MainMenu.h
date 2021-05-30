#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Menu.h"
#include "../Header/PlayerNameMenu.h"
#include "../Header/HowToPlayMenu.h"
#include "../Header/HighScoreMenu.h"
#include "../Header/OptionsMenu.h"
#include "../Header/CreditsMenu.h"

class MainMenu : private Menu
{
	// Properties
private:
	PlayerNameMenu playerName;
	HowToPlayMenu howToPlay;
	HighScoreMenu highScore;
	OptionsMenu options;
	CreditsMenu credits;
	Font menuFont;
	Text menuOptions[6];
	Texture optionShadowTexture;
	Sprite optionShadowSprite;
	int selectedOption;
	
public:
	player newPlayer;
	bool gameRunning;

	// Constractor
	MainMenu();


	// Control all events happend in Menu and its children
	void handleAllEvents(Event event);


	// Draw Menu and its children contents
	void drawAll(RenderWindow& window);


	// Make Menu display
	void checkShow();
private:
	// Draw Main Menu contents
	void draw(RenderWindow& window) override;


	// Handle all event happend on Main Menu
	void catchEvents(Event event) override;


	// Move up to the previous option
	void moveUp();


	// Move to the next option
	void moveDown();


	// Handle what would done when chose specific option
	void mainMenuHandleSelection();

	
};

