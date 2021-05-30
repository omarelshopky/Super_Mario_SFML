#include "../Header/Menu.h"


void Menu::setBackText() {
	// Load font from file
	if (!this->font.loadFromFile(CAIRO_REGULAR)) { std::cout << "Can't load CAIRO_REGULAR\n"; }

	backText.setString("press esc to back");
	backText.setFont(font);
	backText.setCharacterSize(30);
	backText.setPosition(1350.0, 855.0);
}


void Menu::draw(RenderWindow& window) {
	if (display) {
		window.draw(backGroundSprite);
		window.draw(backText);
	}
}


void Menu::catchEvents(Event event) {
	if (display) {
		// Handle event that make user return back to Main Menu
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
			this->hide();
		}
			
	}
}


void Menu::show() {
	display = true;
}


void Menu::hide() {
	display = false;
}


