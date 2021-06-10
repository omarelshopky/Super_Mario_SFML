#include "../Header/MainMenu.h"


MainMenu::MainMenu()
{
	// Set initial values
	this->show();
	selectedOption = 0;	
	newPlayer.lifes = 3;
	gameRunning = false;

	// Load fonts from file
	if (!menuFont.loadFromFile(MAIN_MENU_FONT)) { std::cout << "Can't load MAIN_MENU_FONT\n"; }

	// Load backgrounds
	if (!backGroundTexture.loadFromFile(MAIN_MENU_BACKGROUND)) { std::cout << "Can't load MAIN_MENU_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);

	// Set OptionShadow Properties
	if (!optionShadowTexture.loadFromFile(MENU_SHADOW)) { std::cout << "Can't load MENU_SHADOW\n"; }
	optionShadowSprite.setTexture(optionShadowTexture);
	optionShadowSprite.setColor(Color(255, 255, 255, 100));
	optionShadowSprite.setPosition(620, 295 + selectedOption * 70);

	setChangeOptionSound();

	// Helper varibles
	float width = 628;
	float hight = 225;
	std::string OptionsTemp[6] = {
		"	  START",
		"HOW TO PLAY",
		"HIGH  SCORES",
		"    OPTIONS",
		"    CREDITS",
		"       EXIT" };

	for (int i = 0; i < 6; i++) {
		menuOptions[i].setFont(menuFont);
		menuOptions[i].setFillColor(sf::Color::White);
		menuOptions[i].setCharacterSize(43);
		menuOptions[i].setStyle(sf::Text::Bold);
		menuOptions[i].setString(OptionsTemp[i]);

		hight += 70;
		menuOptions[i].setPosition(width, hight);
	}
}


void MainMenu::handleAllEvents(Event event) {
	this->catchEvents(event);
	playerName.catchEvents(event , newPlayer);
	howToPlay.catchEvents(event);
	highScore.catchEvents(event);
	options.catchEvents(event, newPlayer);
	credits.catchEvents(event);
}


void MainMenu::catchEvents(Event event) {
	if (display) {
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Up:
				this->moveUp();
				changingOptionSound.play();
				break;
			case Keyboard::Down:
				this->moveDown();
				changingOptionSound.play();
				break;
			case Keyboard::Enter:
				mainMenuHandleSelection();
				changingOptionSound.play();
				break;
			}
			break;
		}
	}
}


void MainMenu::drawAll(RenderWindow& window) {
	this->draw(window);
	playerName.draw(window);
	howToPlay.draw(window);
	highScore.draw(window);
	options.draw(window);
	credits.draw(window);
}


void MainMenu::draw(RenderWindow& window) {
	checkShow();
	controlMusic();
	if (display) {
		window.draw(backGroundSprite);
		window.draw(optionShadowSprite);

		for (int i = 0; i < 6; i++) {
			window.draw(menuOptions[i]);
		}
	}
}


void MainMenu::checkShow() {
	gameRunning = playerName.levelsList.gameEngine.gameRunning;
	
	bool allFormsClose = ((!playerName.display && !howToPlay.display) && (!highScore.display && !options.display))
						&& (!credits.display && !playerName.levelsList.display);
	if (allFormsClose && !gameRunning) show();
}


void MainMenu::moveDown()
{
	// if box in Exit postion set to Start 
	if (optionShadowSprite.getPosition().y == 645)
	{
		optionShadowSprite.setPosition(620, 295);
		selectedOption = 0;
	}
	else {
		optionShadowSprite.move(0, 70);
		selectedOption++;
	}
}


void MainMenu::moveUp()
{
	// if box in Start postion set to Exit 
	if (optionShadowSprite.getPosition().y == 295)
	{
		optionShadowSprite.setPosition(620, 645);
		selectedOption = 5;
	}
	else {
		optionShadowSprite.move(0, -70);
		selectedOption--;
	}
}



void MainMenu::mainMenuHandleSelection() {
	// Check current selected option
	this->hide();
	switch (selectedOption)
	{
	case 0:
		playerName.show();
		controlEnemiesSpeed();
		break;
	case 1:
		howToPlay.show();
		break;
	case 2:
		highScore.show();
		break;
	case 3:
		options.show();
		break;
	case 4:
		credits.show();
		break;
	case 5:
		exit(0);
		break;
	}
}


void MainMenu::controlMusic() {
	if (gameRunning) {
		if (options.levelSound.getStatus() == options.levelSound.Stopped)
			options.levelSound.play();

		if (options.menuSound.getStatus() == options.menuSound.Playing)
			options.menuSound.stop();
	}
}


void MainMenu::controlEnemiesSpeed() {
	switch (newPlayer.lifes)
	{
	case 5:
		newPlayer.enemiesSpeed = 2;
		break;
	case 3:
		newPlayer.enemiesSpeed = 3;
		break;
	case 1:
		newPlayer.enemiesSpeed = 7;
		break;
	default:
		break;
	}
}