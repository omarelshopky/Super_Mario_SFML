/***		Include Modules			***/
#include "../Header/DEFINITION.h"
#include "../Header/Blocks.h"
#include "../Header/Enemy.h"
#include "../Header/GameEngine.h"
#include "../Header/Items.h"
#include "../Header/Mario.h"
#include "../Header/Menu.h"


int main()
{
	// Hide Console open when run the game
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// Open Startup Game Window 
	RenderWindow window(sf::VideoMode(1600, 900), "Super Mario");
	
	// Create New Mario
	Mario mario = Mario();
	//mario.bigState();
	
	// Create GameEnigne and Menu
	GameEngine gameEngine = GameEngine(window);
    Menu menu = Menu();

	bool omar = true;
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
				gameEngine.timeToScore();
			}
			
			

            menu.catchEvents(event, window);
		}

		// Mario movement
		mario.move();
		gameEngine.updateTimer();
		if (omar) {
			gameEngine.updateScore(12);
			gameEngine.addPlayerInfo("ayman");
			gameEngine.sortPlayersFile();
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
        menu.draw(window);
  		/// Draw what you do in screen


	  	           
		window.display();
	}
	return 0;
}

