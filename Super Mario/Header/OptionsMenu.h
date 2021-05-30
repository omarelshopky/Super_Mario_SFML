#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Menu.h"

class OptionsMenu : public Menu
{
private:
	/***			Properties				***/
	Texture optionShadowTexture, musicBallTexture, difficultyBallTexture, controlBallTexture;
	Sprite optionShadowSprite, musicBallSprite, difficultyBallSprite, controlBallSprite;
	SoundBuffer menuBuffer;
	Sound menuSound;
	int activeSlide, selectedDifficulty;

public:
	bool muteMusic, handControlled;

	// Constructor
	OptionsMenu();


	/***			Methods				***/

	// Draw Menu contents
	void draw(RenderWindow& window) override;


	// Handle all event happend on Options Menu
	void catchEvents(Event event, player& newPlayer);

	
	// Move Right between Options slides (music , control and difficulty)
	void moveRight();


	// Move Left between Options slides (music , control and difficulty)
	void moveLeft();


	// handle move Up and Down in Options Slides
	void changeSettings(bool up, player newPlayer);


	// Change Music ball (on and off)
	void changeActiveMusicOption();


	// mute Music
	void updateMusicSettings();


	// Change Control ball (Keyboard or Hand)
	void changeActiveControlOption();


	// Start hand control script
	void updateControlSettings();


	// Change Difficulty ball (Keyboard or Hand)
	void changeActiveDifficultyOption(bool up, player newPlayer);


	// Change how many lifes player have according to his choise
	void updateDifficultySettings(player newPlayer);
};

