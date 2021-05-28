#pragma once
#include "../Header/DEFINITION.h"


class Menu
{
	// Menu properties
private:
	bool mainMenuDisplay, playerNameDisplay, highScoreDisplay, levelsListDisplay;
	int selectedOption;
	Font menuFont, playerNameFont;
	String playerNameStr;
	Text menuOptions[6], playerNameText, highScoreText[10][2], backButtonText;
	Texture optionShadowTexture, backGroundTexture, playerNameTexture, highScoreTexture;
	Sprite optionShadowSprite, backGroundSprite, playerNameSprite, highScoreSprite;
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


	// Make Main menu display
	void openMainMenu();


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