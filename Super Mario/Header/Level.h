#pragma once
#include "../Header/DEFINITION.h"


class Level
{
	/***			Properties				***/
public:
	bool display;
protected:
	Texture backGroundTexture;
	Sprite backGroundSprite;

public:
	/***			Methods				***/
	// Draw Levels contents
	virtual void draw(RenderWindow& window);


	// Control all level event
	virtual void catchEvents(Event event);

	// Make Level start
	virtual void start();

	// Close Menu
	virtual void end();
};

