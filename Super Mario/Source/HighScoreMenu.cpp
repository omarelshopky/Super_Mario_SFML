#include "../Header/HighScoreMenu.h"

HighScoreMenu::HighScoreMenu() {
	display = false;

	// Set Back Text Properties
	setBackText();

	setChangeOptionSound();

	// Load background
	if (!backGroundTexture.loadFromFile(HIGH_SCORE_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);

	// Set High Score Texts Properties
	highScoresPos.x = 440;
	highScoresPos.y = 185;
	for (int i = 0; i < 10; i++) {
		highScoreText[i][0].setFont(font);
		highScoreText[i][1].setFont(font);

		highScoreText[i][0].setCharacterSize(40);
		highScoreText[i][1].setCharacterSize(40);

		highScoreText[i][0].setPosition(highScoresPos.x, highScoresPos.y);
		highScoreText[i][1].setPosition(highScoresPos.x + 600, highScoresPos.y);
		highScoresPos.y += 56.5;
	}
}


void HighScoreMenu::draw(RenderWindow& window) {
	if(display) {
		window.draw(backGroundSprite);
		window.draw(backText);
		for (int i = 0; i < 10; i++) {
			window.draw(highScoreText[i][0]);
			window.draw(highScoreText[i][1]);
		}
	}
}


void HighScoreMenu::show() {
	display = true;
	fillHighScore();
}


void HighScoreMenu::fillHighScore() {
	sortPlayersFile();

	for (int i = 0; i < 10; i++) {
		highScoreText[i][0].setString(players[i].second.second);
		highScoreText[i][1].setString(to_string(players[i].first));
	}
}


void HighScoreMenu::sortPlayersFile() {
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


void HighScoreMenu::arrangePlayersInfo() {
	int lines = getNumberOfLines();
	player tempPlayer;

	playersFile.open(PLAYERS_FILE);

	// Add players information to vector
	for (int i = 0; i < lines; i++) {
		playersFile >> tempPlayer.name >> tempPlayer.score >> tempPlayer.level;
		players.push_back({ atoi(tempPlayer.score.c_str()), {atoi(tempPlayer.level.c_str()), tempPlayer.name} });
	}

	playersFile.close();
	playersFile.clear();
}


int HighScoreMenu::getNumberOfLines() {
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