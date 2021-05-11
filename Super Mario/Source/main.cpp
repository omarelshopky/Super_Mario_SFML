/***		Include SFML files			***/
#include <SFML/Graphics.hpp>

/***		Include Modules			***/
#include "../Header/Blocks.h"
#include "../Header/Enemy.h"
#include "../Header/GameEngine.h"
#include "../Header/Items.h"
#include "../Header/Mario.h"
#include "../Header/Menu.h"

using namespace sf;

int main()
{
	// Open Startup Game Window 
	RenderWindow window(sf::VideoMode(1600, 900), "Super Mario");
	
	// Create New Mario
	Mario mario = Mario();

	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Close the game when Cross button right most the form clicked
			if (event.type == Event::Closed)
			{
				window.close();
			}
			
			/// Try your code here










			// /// /////////////////////////////////////////////////
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				mario.Mario_Sprite.setScale(1, 1);
				mario.Mario_Sprite.move(15, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				mario.Mario_Sprite.setScale(-1, 1);
				mario.Mario_Sprite.move(-15, 0);
			}
			// /// /////////////////////////////////////////////////
		}

		window.clear();
		window.draw(mario.Mario_Sprite);
		/// Draw what you do in screen 





		/// ////////////////////////////////////
		window.display();
	}
	return 0;
}