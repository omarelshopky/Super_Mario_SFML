#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Menu.h"

class PlayerNameMenu : public Menu
{
private:
	/***			Properties				***/
	Text playerNameText;
	String playerNameStr;

public:
	// Constructor
	PlayerNameMenu();


	/***			Methods				***/

	// Draw Menu contents
	void draw(RenderWindow& window) override;


	//Handle all event happend on Player Name window
	void catchEvents(Event event, player& newPlayer);
};

