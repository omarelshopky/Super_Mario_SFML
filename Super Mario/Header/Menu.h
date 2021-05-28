#pragma once
#include "../Header/DEFINITION.h"


class Menu
{
	// Menu properties
private:
	bool mainMenuDisplay, playerNameDisplay, highScoreDisplay, levelsListDisplay, howToPlayDisplay, optionsDisplay, creditsDisplay,
		handControlled;
	int selectedOption, activeOptionsMenu;
	Font menuFont, playerNameFont;
	String playerNameStr;
	Text menuOptions[6], playerNameText, highScoreText[10][2], backText;
	Texture optionShadowTexture, backGroundTexture, playerNameTexture, highScoreTexture, howToPlayTexture, optionsTexture, creditsTexture,
		musicBallTexture, difficultyBallTexture, controlBallTexture;
	Sprite optionShadowSprite, backGroundSprite, playerNameSprite, highScoreSprite, howToPlaySprite, optionsSprite, creditsSprite,
		musicBallSprite, difficultyBallSprite, controlBallSprite;
	fstream playersFile;
	vector <pair<int, pair<int, string>>> players;
	position highScoresPos;
	player newPlayer;
	SoundBuffer menuBuffer;
	Sound menuSound;

public:
	bool muteMusic;

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


	// Make Main menu display
	void openMainMenu();


	// Make player name menu display
	void openPlayerName();


	// Make high score menu display
	void openHighScore();


	// Make Main menu display
	void openHowToPlay();


	// Make Options menu display
	void openOptions();


	// Make Credits display
	void openCredits();
	

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


	// change between music , control and difficulty
	void changeOptionsMenu(bool Right);


	// Change Music ball (on and off)
	void changeActiveMusicOption();


	// Mute music 
	void updateMusicSettings();


	// Change Control ball (Keyboard or Hand)
	void changeActiveControlOption();


	// Start hand control script
	void updateControlSettings();
};