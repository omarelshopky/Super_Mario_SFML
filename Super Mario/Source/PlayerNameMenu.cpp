#include "../Header/PlayerNameMenu.h"


PlayerNameMenu::PlayerNameMenu() {
	display = false;

	// Set Back Text Properties
	setBackText();

	setChangeOptionSound();

	// Load background
	if (!backGroundTexture.loadFromFile(PLAYER_NAME_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);


	// Set Player Name Text Properties
	playerNameText.setFont(font);
	playerNameText.setCharacterSize(70);
	playerNameText.setStyle(Text::Style::Bold);
	playerNameText.setPosition(447, 411);
}


void PlayerNameMenu::draw(RenderWindow& window) {
	if (display) {
		window.draw(backGroundSprite);
		window.draw(playerNameText);
		window.draw(backText);
	}
	levelsList.draw(window);
}


void PlayerNameMenu::catchEvents(Event event, player& newPlayer) {
	if (display) {
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Backspace:
				// Erase last character form string
				playerNameStr = playerNameStr.substring(0, playerNameStr.getSize() - 1);
				playerNameText.setString(playerNameStr);
				changingOptionSound.play();
				break;
			case sf::Keyboard::Enter:
				if (!playerNameStr.isEmpty()) {
					this->hide();

					// Convert sfml String to std String
					newPlayer.name = std::string(playerNameStr);

					playerNameStr = ""; // To Clean last inputed name
					playerNameText.setString(playerNameStr);

					levelsList.show(newPlayer);
				}
				changingOptionSound.play();
				break;
			case Keyboard::Escape:
				this->hide();
				changingOptionSound.play();
				break;
			}
			break;

		case Event::TextEntered:
			bool notForbidinKeys = (!Keyboard::isKeyPressed(Keyboard::Enter) && !Keyboard::isKeyPressed(Keyboard::BackSpace)) && (!Keyboard::isKeyPressed(Keyboard::Escape) && !Keyboard::isKeyPressed(Keyboard::Space));
			if (playerNameStr.getSize() <= 20 && notForbidinKeys) {
				if(event.text.unicode < '0' || event.text.unicode > '9')
					playerNameStr += event.text.unicode;
				playerNameText.setString(playerNameStr);
			}
			break;
		}
	}
	levelsList.catchEvents(event, newPlayer);
}


