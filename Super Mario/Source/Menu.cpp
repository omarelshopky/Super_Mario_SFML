#include "../Header/Menu.h"


Menu::Menu()
{
	// Set initial values
	openMainMenu();
	selectedOption = 0;

	// Load fonts from file
	if (!menuFont.loadFromFile(MAIN_MENU_FONT)) { std::cout << "Can't load MAIN_MENU_FONT\n"; }
	if (!playerNameFont.loadFromFile(PLAYER_NAME_FONT)) { std::cout << "Can't load PLAYER_NAME_FONT\n"; }

	// Load backgrounds
	if(!backGroundTexture.loadFromFile(MAIN_MENU_BACKGROUND)) { std::cout << "Can't load MAIN_MENU_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);

	if (!playerNameTexture.loadFromFile(PLAYER_NAME_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	playerNameSprite.setTexture(playerNameTexture);

	if (!highScoreTexture.loadFromFile(HIGH_SCORE_BACKGROUND)) { std::cout << "Can't load HIGH_SCORE_BACKGROUND\n"; }
	highScoreSprite.setTexture(highScoreTexture);


	// Set OptionShadow properties
	if(!optionShadowTexture.loadFromFile(MENU_SHADOW)) { std::cout << "Can't load MENU_SHADOW\n"; }
	optionShadowSprite.setTexture(optionShadowTexture);
	optionShadowSprite.setPosition(620, 295); // Start position 

	// Set Back Button Text Properties
	backButtonText.setString("press esc to back");
	backButtonText.setFont(playerNameFont);
	backButtonText.setCharacterSize(30);
	backButtonText.setPosition(1190, 760);

	// Set Player Name Text Properties
	playerNameText.setFont(playerNameFont);
	playerNameText.setCharacterSize(70);
	playerNameText.setStyle(Text::Style::Bold);
	playerNameText.setPosition(447, 411);

	// Set High Score Text Properties
	highScoresPos.x = 440;
	highScoresPos.y = 185;
	for (int i = 0; i < 10; i++) {
		highScoreText[i][0].setFont(playerNameFont);
		highScoreText[i][1].setFont(playerNameFont);

		highScoreText[i][0].setCharacterSize(40);
		highScoreText[i][1].setCharacterSize(40);

		highScoreText[i][0].setPosition(highScoresPos.x, highScoresPos.y);
		highScoreText[i][1].setPosition(highScoresPos.x + 600, highScoresPos.y);
		highScoresPos.y += 56.5;
	}
	

	// Helper varibles
	float width = 628;
	float hight = 225;
	std::string OptionsTemp[6] = {
		"	  START",
		"HOW TO PLAY",
		"HIGH  SCORES",
		"    OPTIONS",
		"    CREDITS",
		"       EXIT"};

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


void Menu::draw(RenderWindow& window)
{
	if (mainMenuDisplay) {
		window.draw(backGroundSprite);
		window.draw(optionShadowSprite);

		for (int i = 0; i < 6; i++) {
			window.draw(menuOptions[i]);
		}
	}
	else if (playerNameDisplay) {
		window.draw(playerNameSprite);
		window.draw(playerNameText);
	}
	else if (highScoreDisplay) {
		window.draw(highScoreSprite);
		for (int i = 0; i < 10; i++) {
			window.draw(highScoreText[i][0]);
			window.draw(highScoreText[i][1]);
		}
	}

	if (!mainMenuDisplay) {
		window.draw(backButtonText);
	}
}


void Menu::moveDown()
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


void Menu::moveUp()
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


void Menu::catchEvents(Event& event, RenderWindow& window) {
	if (mainMenuDisplay) {
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Up:
				this->moveUp();
				break;
			case Keyboard::Down:
				this->moveDown();
				break;
			case Keyboard::Enter:
				mainMenuHandleSelection();
				break;
			}
			break;
		}
	}
	else if (playerNameDisplay) {
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Backspace:
				// Erase last character form string
				playerNameStr = playerNameStr.substring(0, playerNameStr.getSize() - 1);
				playerNameText.setString(playerNameStr);
				break;
			case sf::Keyboard::Enter:
				if (!playerNameStr.isEmpty()) {
					playerNameDisplay = false;

					// Convert sfml String to std String
					playerName = std::string(playerNameStr);
				}
				break;
			case Keyboard::Escape:
				openMainMenu();
				break;
			}
			break;

		case Event::TextEntered:
			if (playerNameStr.getSize() <= 20 && !Keyboard::isKeyPressed(Keyboard::Enter) && !Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				playerNameStr += event.text.unicode;
				playerNameText.setString(playerNameStr);
			}
			break;
		}
	}
	else if (highScoreDisplay) {
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Escape:
				openMainMenu();
				break;
			}
			break;
		}
	}
}


void Menu::openMainMenu() {
	mainMenuDisplay = true;
	playerNameDisplay = false;
	highScoreDisplay = false;
}


void Menu::openPlayerName() {
	playerNameDisplay = true;
	mainMenuDisplay = false;
}


void Menu::openHighScore() {
	highScoreDisplay = true;
	mainMenuDisplay = false;
	fillHighScore();
}


void Menu::mainMenuHandleSelection() {
	// Check current selected option
	switch (selectedOption)
	{
	case 0:
		openPlayerName();
		break;
	case 2:
		openHighScore();
		break;
	case 5:
		exit(0);
		break;
	}
}


int Menu::getNumberOfLines() {
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


void Menu::arrangePlayersInfo() {
	int lines = getNumberOfLines();
	player newPlayer;

	playersFile.open(PLAYERS_FILE);

	// Add players information to vector
	for (int i = 0; i < lines; i++) {
		playersFile >> newPlayer.name >> newPlayer.score >> newPlayer.level;
		players.push_back({ atoi(newPlayer.score.c_str()), {atoi(newPlayer.level.c_str()), newPlayer.name} });
	}

	playersFile.close();
	playersFile.clear();
}


void Menu::sortPlayersFile() {
	// Clear all players from vector
	players.clear();

	// get data from players file
	arrangePlayersInfo();

	// sort scores
	sort(players.rbegin(), players.rend());


	playersFile.open(PLAYERS_FILE);

	for (int i = 0; i < players.size(); i++) {
		playersFile << players[i].second.second << ' ' << players[i].first << ' ' << players[i].second.first << '\n';
	}
	playersFile.close();
	playersFile.clear();
}


void Menu::fillHighScore() {
	sortPlayersFile();

	for (int i = 0; i < 10; i++) {
		highScoreText[i][0].setString(players[i].second.second);
		highScoreText[i][1].setString(to_string(players[i].first));
	}
}