/***		Include Header			***/
#include "../Header/MainMenu.h"

int main()
{
	/***		Hide Console open when run the game			***/
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	/***			Open Startup Game Window			***/
	RenderWindow window(sf::VideoMode(1600, 900), "Super Mario");
	window.setFramerateLimit(60); // Limit the framerate to a maximum fixed frequency.

	MainMenu menu;  // Create Menu 

	/***			Game Loop			***/
	while (window.isOpen())
	{
		Event event;
		/***			Events Loop				***/
		while (window.pollEvent(event))
		{
			// Close the game when Cross button right most the form clicked
			if (event.type == Event::Closed) window.close();
				
            menu.handleAllEvents(event); // Handle all Events for the Game
		}

		window.clear();
        menu.drawAll(window); // Draw all the Game components
		window.display();
	}
	return 0;
}