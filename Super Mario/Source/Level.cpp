#include "../Header/Level.h"


void Level::draw(RenderWindow& window) {
	if (display) {
		window.draw(backGroundSprite);
	}
}


void Level::catchEvents(Event event) {
	if (display) {
		// Handle event that make user return back to Main Menu
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
			// Pause the game
			this->end();
		}
	}
}


void Level::start() {
	display = true;
}


void Level::end() {
	display = false;
}



