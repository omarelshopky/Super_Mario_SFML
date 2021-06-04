/***		Include Modules			***/
#include "../Header/DEFINITION.h"
#include "../Header/Blocks.h"
#include "../Header/Enemy.h"
#include "../Header/GameEngine.h"
#include "../Header/Items.h"
#include "../Header/Mario.h"
#include "../Header/MainMenu.h"

int main()
{
	/***		Hide Console open when run the game			***/
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	/***			Open Startup Game Window			***/
	RenderWindow window(sf::VideoMode(1600, 900), "Super Mario");
	window.setFramerateLimit(60); // Limit the framerate to a maximum fixed frequency.

	MainMenu menu;  // Create Menu 

	// Create New Mario
	//Mario mario(700, 700);
	bool omar = true;
	Clock timer;
	/***			Game Loop			***/
	while (window.isOpen())
	{
		Event event;
		/***			Events Loop				***/
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) { // Close the game when Cross button right most the form clicked
				window.close(); 
			}

            menu.handleAllEvents(event);
			//mario.catchEvents(event);
		}

		if (omar) {
			/*int cnt = 0;
			while (cnt < 11) {
				if (timer.getElapsedTime().asSeconds() > 0.2) {
					if(cnt % 2 == 0) mario.smallState();
					else mario.bigState();
					cnt++;
					window.clear();
					window.draw(mario.marioSprite);
					window.display();
					timer.restart();
				}
			}*/
			omar = false;
		}

		window.clear();
        menu.drawAll(window);
		//mario.draw(window);
		window.display();
	}
	return 0;
}