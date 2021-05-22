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
	mario.SmallState();
	
	// Create GameEnigne and Menu
	GameEngine gameEngine = GameEngine(window);
    Menu menu = Menu();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Close the game when Cross button right most the form clicked
			if (event.type == Event::Closed){
				window.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Z)) {
				gameEngine.TimeToScore();
			}
			
			mario.CatchEvents();

            menu.CatchEvents(event, window);
		}

		// Mario movement
		mario.Move();
		gameEngine.Update_Timer();
		


		window.clear();
		window.draw(mario.MarioSprite);
		gameEngine.Draw();
        menu.Draw(window);
		/// Draw what you do in screen


		
		window.display();
	}
	return 0;
}

