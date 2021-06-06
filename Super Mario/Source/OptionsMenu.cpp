#include "../Header/OptionsMenu.h"

OptionsMenu::OptionsMenu() {
	// Set initial values
	muteMusic = handControlled = false;
	selectedDifficulty = 2;
	display = false;

	// Set Back Text Properties
	setBackText();

	// Load background
	if (!backGroundTexture.loadFromFile(OPTIONS_BACKGROUND)) { std::cout << "Can't load OPTIONS_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);

	// Set Menu Sound Properties
	if (!menuBuffer.loadFromFile(MENU_SOUND)) { std::cout << "Can't load MENU_SOUND\n"; }
	menuSound.setBuffer(menuBuffer);
	menuSound.setLoop(true);
	menuSound.play();

	// Set Levels Sound Properties
	levelBuffer.loadFromFile(LEVEL_MUSIC);
	levelSound.setBuffer(levelBuffer);
	levelSound.setLoop(true);

	setChangeOptionSound();

	// Set shadow properties
	if (!optionShadowTexture.loadFromFile(MENU_SHADOW)) { std::cout << "Can't load MENU_SHADOW\n"; }
	optionShadowSprite.setTexture(optionShadowTexture);
	optionShadowSprite.setColor(Color(255, 255, 255, 100));
	optionShadowSprite.setPosition(185, 140);
	optionShadowSprite.setScale(0.9, 1);

	// Set Music Ball Properties
	if (!musicBallTexture.loadFromFile(MUSIC_BALL)) { std::cout << "Can't load MUSIC_BALL\n"; }
	musicBallSprite.setTexture(musicBallTexture);
	musicBallSprite.setPosition(482, 410);

	// Set Difficulty Ball Properties
	if (!difficultyBallTexture.loadFromFile(DIFFICULTY_BALL)) { std::cout << "Can't load DIFFICULTY_BALL\n"; }
	difficultyBallSprite.setTexture(difficultyBallTexture);
	difficultyBallSprite.setPosition(1377, 363);

	// Set Control Ball Properties
	if (!controlBallTexture.loadFromFile(CONTROL_BALL)) { std::cout << "Can't load CONTROL_BALL\n"; }
	controlBallSprite.setTexture(controlBallTexture);
	controlBallSprite.setPosition(966, 255);
}


void OptionsMenu::draw(RenderWindow& window) {
	if (display) {
		window.draw(backGroundSprite);
		window.draw(optionShadowSprite);
		window.draw(backText);
		window.draw(musicBallSprite);
		window.draw(controlBallSprite);
		window.draw(difficultyBallSprite);
	}
}


void OptionsMenu::catchEvents(Event event, player& newPlayer) {
	if (display) {
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Right:
				moveRight();
				changingOptionSound.play();
				break;

			case Keyboard::Left:
				moveLeft();
				changingOptionSound.play();
				break;

			case Keyboard::Up:
				changeSettings(true, newPlayer);
				changingOptionSound.play();
				break;

			case Keyboard::Down:
				changeSettings(false, newPlayer);
				changingOptionSound.play();
				break;

			case Keyboard::Escape:
				this->hide();
				changingOptionSound.play();
				break;
			}
			break;
		}
	}
}


void OptionsMenu::moveRight() {
	// if box in Difficulty postion set to Music 
	if (optionShadowSprite.getPosition().x == 1105)
	{
		optionShadowSprite.setPosition(185, 140);
		activeSlide = 0;
	}
	else {
		optionShadowSprite.move(460, 0);
		activeSlide++;
	}
}


void OptionsMenu::moveLeft() {
	// if box in Music postion set to Difficulty 
	if (optionShadowSprite.getPosition().x == 185)
	{
		optionShadowSprite.setPosition(1105, 140);
		activeSlide = 2;
	}
	else {
		optionShadowSprite.move(-460, 0);
		activeSlide--;
	}
}


void OptionsMenu::changeSettings(bool up, player newPlayer) {
	switch (activeSlide) {
	case 0:
		changeActiveMusicOption();
		break;
	case 1:
		changeActiveControlOption();
		break;
	case 2:
		changeActiveDifficultyOption(up, newPlayer);
		break;
	}
}


void OptionsMenu::changeActiveMusicOption() {
	muteMusic = !muteMusic;
	if (muteMusic) {
		musicBallSprite.setPosition(482, 468);
	}
	else {
		musicBallSprite.setPosition(482, 410);
	}
	updateMusicSettings();
}


void OptionsMenu::updateMusicSettings() {
	if (muteMusic) {
		menuSound.pause();
		levelSound.setVolume(0);
	}
	else {
		menuSound.play();
		levelSound.setVolume(100);
	}
}


void OptionsMenu::changeActiveControlOption() {
	handControlled = !handControlled;
	if (handControlled) {
		controlBallSprite.setPosition(966, 450);
	}
	else {
		controlBallSprite.setPosition(966, 255);
	}
	updateControlSettings();
}


void OptionsMenu::updateControlSettings() {
	if (handControlled) {
		//system("python \"../Super Mario/HandControler/HandControl.py\"");
	}
	else {

	}
}


void OptionsMenu::changeActiveDifficultyOption(bool up, player newPlayer) {
	if (up) {
		if (selectedDifficulty == 1) {
			difficultyBallSprite.setPosition(1377, 451);
			selectedDifficulty = 3;
		}
		else {
			difficultyBallSprite.move(0, -88);
			selectedDifficulty--;
		}
	}
	else {
		if (selectedDifficulty == 3) {
			difficultyBallSprite.setPosition(1377, 275);
			selectedDifficulty = 1;
		}
		else {
			difficultyBallSprite.move(0, 88);
			selectedDifficulty++;
		}
	}
	updateDifficultySettings(newPlayer);
}


void OptionsMenu::updateDifficultySettings(player newPlayer) {
	switch (selectedDifficulty)
	{
	case 1:
		newPlayer.lifes = 5;
		break;
	case 2:
		newPlayer.lifes = 3;
		break;
	case 3:
		newPlayer.lifes = 1;
		break;
	default:
		break;
	}
}