#pragma once
#include "../Header/DEFINITION.h"


#define NUM_OF_OPTIONS 6

class Menu
{
	// Menu properties
private:
	bool mainMenuDisplay, playerNameDisplay, highScoreDisplay, levelsListDisplay;
	int selectedOption;
	Font menuFont, playerNameFont;
	Text menuOptions[NUM_OF_OPTIONS];
	Texture optionShadowTexture, backGroundTexture, playerNameTexture, highScoreTexture;
	Sprite optionShadowSprite, backGroundSprite, playerNameSprite, highScoreSprite;
	String playerNameStr;
	Text playerNameText, highScoreText[10][2];
	fstream playersFile;
	vector <pair<int, pair<int, string>>> players;
	position highScoresPos;

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


	// Make high score menu display
	void openHighScore();


	// Handle what would done when chose specific option
	void mainMenuHandleSelection();


	// Make a vector contain players information collected form file
	void arrangePlayersInfo();


	// Count how many lines in specific file 
	int getNumberOfLines();


	// Sort players info according to score
	void sortPlayersFile();


	// Fill High score board with the top 10
	void fillHighScore();
};