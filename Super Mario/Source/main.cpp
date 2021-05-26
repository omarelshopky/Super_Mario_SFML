/***		Include SFML files			***/
#include <SFML/Graphics.hpp>

/***		Include Modules			***/
#include "../Header/Blocks.h"
#include "../Header/Enemy.h"
#include "../Header/GameEngine.h"
#include "../Header/Items.h"
#include "../Header/Mario.h"
#include "../Header/Menu.h"

/***		Include Helper Libraries		***/
#include <windows.h>

using namespace sf;

int main()
{
	// Hide Console open when run the game
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// Open Startup Game Window 
	RenderWindow window(sf::VideoMode(1600, 900), "Super Mario");
	
	// Create New Mario
	Mario mario = Mario();
	//mario.smallState();
	
	// Create GameEnigne and Menu
	GameEngine gameEngine = GameEngine(window);
    Menu menu = Menu();

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
				gameEngine.TimeToScore();
			}
			
			

            menu.CatchEvents(event, window);
		}

		// Mario movement
		mario.move();
		gameEngine.Update_Timer();
		


		window.clear();
		window.draw(mario.marioSprite);                   
		gameEngine.Draw();
        //menu.Draw(window)     ;
  		/// Draw what you do in screen


	 	           
		window.display();
	}
	return 0;
}

