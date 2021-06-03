#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/Menu.h"
#include "../Header/LevelsList.h"

class PlayerNameMenu : public Menu
{
private:
	/***			Properties				***/
	Text playerNameText;
	String playerNameStr;

public:
	LevelsList levelsList;

	// Constructor
	PlayerNameMenu();


	/***			Methods				***/

	// Draw Menu contents
	void draw(RenderWindow& window) override;


	//Handle all event happend on Player Name window
	void catchEvents(Event event, player& newPlayer);
};

