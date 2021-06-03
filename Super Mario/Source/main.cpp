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
	// Hide Console open when run the game
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	// Open Startup Game Window 
	RenderWindow window(sf::VideoMode(1600, 900), "Super Mario");
	window.setFramerateLimit(60); //Limit the framerate to a maximum fixed frequency.

	// Create New Mario
	Mario mario;
	mario.bigState();
	
	// Create GameEnigne and Menu
	GameEngine gameEngine = GameEngine(window);
	MainMenu menu;
	Items coin = Items(COIN, 400, 400);

	bool omar = false;
	Clock timer;
	
	gameEngine.setLevelName("level 1-1");
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {

			case Event::Closed:
				// Close the game when Cross button right most the form clicked
				window.close();
				break;

		
			}
			mario.catchEvents(event);
			
			if (Keyboard::isKeyPressed(Keyboard::Z)) {
				coin.startTextFloat();
				//gameEngine.timeToScore();

			}
			
			
            menu.handleAllEvents(event);
		}

		
		// Mario movement
		mario.move();
		gameEngine.updateTimer();
		if (omar) {
			int cnt = 0;
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
			}
			omar = false;
		}

		window.clear();
 		window.draw(mario.marioSprite);                   
		gameEngine.draw();
		coin.draw(window);
        menu.drawAll(window);
  		/// Draw what you do in screen


	  	           
		window.display();
	}
	return 0;
}


