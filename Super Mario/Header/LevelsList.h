#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Menu.h"

#define NUMBER_OF_LEVELS 2

class LevelsList : public Menu
{
private:
	/***			Properties				***/
	Text levelsNameText[NUMBER_OF_LEVELS];
	Texture optionShadowTexture;
	Sprite optionShadowSprite;
	int selectedLevel, maxLevel;
	player currentPlayer;
	fstream playersFile;

public:
	// Constructor
	LevelsList();


	/***			Methods				***/

	// Draw Menu contents
	void draw(RenderWindow& window) override;


	//Handle all event happend on Levels List window
	void catchEvents(Event event, player& newPlayer);


	// Make Menu display
	void show(player newPlayer);

private:
	// Search for player name in files to get his last checkpoint
	void checkOpendLevels();


	// Make available levels look special
	void setOpendLevels();


	// Get how many lines in players file
	int getNumberOfLines();


	// Move up to the previous level
	void moveUp();


	// Move to the next level
	void moveDown();
};

