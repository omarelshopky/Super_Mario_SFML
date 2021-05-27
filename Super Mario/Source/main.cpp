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

#include<iostream>
using namespace sf;

//int main()
//{
//	// Hide Console open when run the game
//	ShowWindow(GetConsoleWindow(), SW_HIDE);
//
//	// Open Startup Game Window 
//	RenderWindow window(sf::VideoMode(1600, 900), "Super Mario");
//	
//	// Create New Mario
//	Mario mario = Mario();
//	//mario.bigState();
//	
//	// Create GameEnigne and Menu
//	GameEngine gameEngine = GameEngine(window);
//    Menu menu = Menu();
//
//	bool omar = false;
//	Clock timer;
//
//	while (window.isOpen())
//	{
//		Event event;
//		while (window.pollEvent(event))
//		{
//			switch (event.type) {
//
//			case Event::Closed:
//				// Close the game when Cross button right most the form clicked
//				window.close();
//				break;
//
//			
//				
//
//			}
//			mario.catchEvents(event);
//			
//			if (Keyboard::isKeyPressed(Keyboard::Z)) {
//				gameEngine.TimeToScore();
//			}
//			
//			
//
//            menu.CatchEvents(event, window);
//		}
//
//		// Mario movement
//		mario.move();
//		gameEngine.Update_Timer();
//		if (omar) {
//			int cnt = 0;
//			while (cnt < 11) {
//				if (timer.getElapsedTime().asSeconds() > 0.2) {
//					if(cnt % 2 == 0) mario.smallState();
//					else mario.bigState();
//					cnt++;
//					window.clear();
//					window.draw(mario.marioSprite);
//					window.display();
//					timer.restart();
//				}
//			}
//			omar = false;
//		}
//
//
//		window.clear();
// 		window.draw(mario.marioSprite);                   
//		gameEngine.Draw();
//        //menu.Draw(window);
//  		/// Draw what you do in screen
//
//
//	  	           
//		window.display();
//	}
//	return 0;
//}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
    Texture image;
    image.loadFromFile("Resource/Textures/Menu/playerName.jpg");
    Sprite sprite;
    sprite.setTexture(image);


    String playerInput;
    Text playerText;
    Font textFont;
    textFont.loadFromFile("Resource/Fonts/Cairo-Regular.ttf");
    playerText.setFont(textFont);
    playerText.setStyle(Text::Style::Bold);
    playerText.setCharacterSize(70);
    playerText.setFillColor(Color::White);
    playerText.setPosition(445, 411);

    bool userInput = true;
        
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered && playerInput.getSize() <= 20)
            {
                playerInput += event.text.unicode;
                playerText.setString(playerInput);
                //std::cout << playerInput.getSize();
            }
            if (Keyboard::isKeyPressed(Keyboard::BackSpace))
            {
                playerInput = playerInput.substring(0, playerInput.getSize() - 1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                userInput = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Z))
            {
                exit(0);
            }
        }


        window.clear();
        if (userInput) {
            window.draw(sprite);
            window.draw(playerText);
        }
        
        window.display();
    }

    return 0;
}