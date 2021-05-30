#pragma once
#include "../Header/DEFINITION.h"

class Menu
{
	/***			Properties				***/
public:
	bool display;
protected:
	Font font;
	Text backText;
	Texture backGroundTexture;
	Sprite backGroundSprite;


public:
	/***			Methods				***/
	// Draw Menu Options
	virtual void draw(RenderWindow& window);


	// Control Menu events
	virtual void catchEvents(Event event);

	// Make Menu display
	virtual void show();

	// Close Menu
	virtual void hide();

protected:
	// Set Back Text Properties
	virtual void setBackText();
};