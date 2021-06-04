#pragma once
#include "../Header/DEFINITION.h"

class Mario
{	
	// Mario properties
private:
	Clock timer1, timer2;
	float marioAcceleration[2], marioSpeed[2];
	bool goRight, goUp, goLeft, goDown, jumping;
	float startJumpPosition;
	area marioArea;

public:
	Texture marioTexture;
	Sprite marioSprite;
	marioState_t marioState;
	
	
	// Constractor
	Mario(float x, float y);


	// Draw mario on screen 
	void draw(RenderWindow& window);


	// set Mario to small state
	void smallState();

	// set Mario to Big state
	void bigState();

	// Move mario
	void move();

	void catchEvents(Event& event);

private:
	// Make animation for mario while walking
	void setMarioRectForWalk(IntRect& intRect);

	// Make mario animation stand still 
	void standStill();

	// make mario jump
	void jump(IntRect& intRect, int RectPosition, float waiting);

	// make mario walk to the right
	void moveRight(IntRect& intRect);

	// make mario walk to the left
	void moveLeft(IntRect& intRect);
};

