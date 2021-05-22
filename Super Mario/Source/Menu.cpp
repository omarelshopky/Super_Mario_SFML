#include "../Header/Menu.h"


Menu::Menu()
{
	// Set initial values
	SelectedOption = 0;

	// Load font from file
	if (!MenuFont.loadFromFile("Resource/Fonts/Barkentina_font.ttf")) {}
	
	// Load background 
	BackGroundTexture.loadFromFile("Resource/Textures/Backgrounds/Menu.jpg");
	BackGroundSprite.setTexture(BackGroundTexture);

	// Set OptionShadow properties
	OptionShadowTexture.loadFromFile("Resource/Textures/MenuShadow.png");
	OptionShadowSprite.setTexture(OptionShadowTexture);
	OptionShadowSprite.setPosition(620, 295); // Start position 

	// Helper varibles
	float width = 628;
	float hight = 225;
	std::string OptionsTemp[NUM_OF_OPTIONS] = {
		"	  START",
		"HOW TO PLAY",
		"HIGH  SCORES",
		"    OPTIONS",
		"    CREDITS",
		"       EXIT"};

	for (int i = 0; i < NUM_OF_OPTIONS; i++) {
		MenuOptions[i].setFont(MenuFont);
		MenuOptions[i].setFillColor(sf::Color::White);
		MenuOptions[i].setCharacterSize(43);
		MenuOptions[i].setStyle(sf::Text::Bold);
		MenuOptions[i].setString(OptionsTemp[i]);
		
		hight += 70;
		MenuOptions[i].setPosition(width, hight);
	}
}


void Menu::Draw(RenderWindow& window)
{
	window.draw(BackGroundSprite);
	window.draw(OptionShadowSprite);
	
	for (int i = 0; i < NUM_OF_OPTIONS; i++) {
		window.draw(MenuOptions[i]);
	}
}


int  Menu::GetSelectedOption() {
	return SelectedOption;
}


void Menu::MoveDown()
{
	// if box in Exit postion set to Start 
	if (OptionShadowSprite.getPosition().y == 645)
	{
		OptionShadowSprite.setPosition(620, 295);
		SelectedOption = 0;
	}
	else {
		OptionShadowSprite.move(0, 70);
		SelectedOption++;
	}
}


void Menu::MoveUp()
{
	// if box in Start postion set to Exit 
	if (OptionShadowSprite.getPosition().y == 295)
	{
		OptionShadowSprite.setPosition(620, 645);
		SelectedOption = 5;
	}
	else {
		OptionShadowSprite.move(0, -70);
		SelectedOption--;
	}
}


void Menu::CatchEvents(Event& event, RenderWindow& window) {
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up) {
			this->MoveUp();
		}
		else if (event.key.code == sf::Keyboard::Down) {
			this->MoveDown();
		}
		else if (event.key.code == sf::Keyboard::Return){//enter
			
			window.close();
		}
		else{/*  Do Nothing  */ }
	}
}
