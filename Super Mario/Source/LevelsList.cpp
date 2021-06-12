#include "../Header/LevelsList.h"

LevelsList::LevelsList() : level1(gameEngine), level2(gameEngine) {
	// Set intial values
	display = false;
	selectedLevel = 0;
	maxLevel = 1;

	// Set Back Text Properties
	setBackText();

	setChangeOptionSound();

	// Load background
	if (!backGroundTexture.loadFromFile(LEVELS_LIST_BACKGROUND)) { std::cout << "Can't load LEVELS_LIST_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);

	// Set OptionShadow Properties
	if (!optionShadowTexture.loadFromFile(MENU_SHADOW)) { std::cout << "Can't load MENU_SHADOW\n"; }
	optionShadowSprite.setTexture(optionShadowTexture);
	optionShadowSprite.setColor(Color(200, 0, 0, 80));
	optionShadowSprite.setPosition(695, 350 + selectedLevel * 200);
	optionShadowSprite.setScale(0.6, 1);

	// Set levels Name Text Properties
	for (int i = 0; i < NUMBER_OF_LEVELS; i++) {
		levelsNameText[i].setFont(font);
		levelsNameText[i].setCharacterSize(50);
		levelsNameText[i].setString("Level " + to_string(i + 1));
		levelsNameText[i].setPosition(720, 350 + i * 200);
	}
}


void LevelsList::show(player newPlayer) {
	display = true;
	gameEngine.currentPlayer = newPlayer;

	selectedLevel = 0;
	optionShadowSprite.setPosition(695, 350 + selectedLevel * 200);

	// Find the last level this player has finished
	checkOpendLevels();
}


void LevelsList::draw(RenderWindow& window) {
	//cout << level1.finished;
	if (display || level1.finished) {
		window.draw(backGroundSprite);
		window.draw(optionShadowSprite);
		window.draw(backText);
		for (int i = 0; i < NUMBER_OF_LEVELS; i++) {
			window.draw(levelsNameText[i]);
		}
	}
	else {
		level1.draw(window);
		level2.draw(window);
	}
}


void LevelsList::catchEvents(Event event, player& newPlayer) {
	if (display) {
		switch (event.type)
		{
		case Event::KeyPressed:
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
				this->hide();
				gameEngine.gameRunning = true;
				switch (selectedLevel) {
				case 0:
					level1.start();
					break;
				case 1:
					level2.start();
					break;
				}
				break;
			case Keyboard::Escape:
				this->hide();
				newPlayer.name = "";
				changingOptionSound.play();
				break;
			}
			break;
		}
	}

	level1.catchEvents(event);
	level2.catchEvents(event);
}


void LevelsList::checkOpendLevels() {
	int lines = getNumberOfLines();
	player tempPlayer;

	playersFile.open(PLAYERS_FILE);

	// Add players information to vector
	for (int i = 0; i < lines; i++) {
		playersFile >> tempPlayer.name >> tempPlayer.score >> tempPlayer.level;
		if (tempPlayer.name == gameEngine.currentPlayer.name) {
			maxLevel = stoi(tempPlayer.level);
			break;
		}
	}

	playersFile.close();
	playersFile.clear();

	setOpendLevels();
}


int LevelsList::getNumberOfLines() {
	// Open the file to read 
	playersFile.open(PLAYERS_FILE);

	// Count how many lines in the file
	int cnt = 0;
	string temp;
	while (getline(playersFile, temp)) cnt++;

	playersFile.close();
	playersFile.clear();

	return cnt;
}


void LevelsList::setOpendLevels() {
	for (int i = 0; i < NUMBER_OF_LEVELS; i++) {
		levelsNameText[i].setFillColor(Color::White);
		if(i >= maxLevel)
			levelsNameText[i].setFillColor(Color::Color(80, 80, 80));
	}
}


void LevelsList::moveDown()
{
	// if box in last postion set to first 
	if (selectedLevel < maxLevel) {
		if (selectedLevel == maxLevel - 1)
		{
			selectedLevel = 0;
		}
		else {
			selectedLevel++;
		}
	}
	optionShadowSprite.setPosition(695, 350 + selectedLevel * 200);
}


void LevelsList::moveUp()
{
	if (selectedLevel < maxLevel) {
		// if box in first postion set to last 
		if (selectedLevel == 0)
		{
			selectedLevel = maxLevel - 1;
		}
		else {
			selectedLevel--;
		}
	}
	optionShadowSprite.setPosition(695, 350 + selectedLevel * 200);
}