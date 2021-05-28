#pragma once
#include "../Header/DEFINITION.h"


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
	fstream playersFile;
	vector <pair<int, pair<int, string>>> players;

public:
	std::string playerName;

	// Constractor
	Menu(); 


	// Draw Menu Options
	void draw(RenderWindow& window);


	// Control Menu events
	void catchEvents(Event& event, RenderWindow& window);

	
	// Sort players info according to score
	void sortPlayersFile();
	

private:
	// Move up to the previous option
	void moveUp();


	// Move to the next option
	void moveDown();


	// Make player name menu display
	void openPlayerName();


	// Handle what would done when chose specific option
	void mainMenuHandleSelection();


	// Make a vector contain players information collected form file
	void arrangePlayersInfo();


	// Count how many lines in specific file 
	int getNumberOfLines();
};