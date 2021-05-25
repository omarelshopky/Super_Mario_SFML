#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

// Make enum for mario state
typedef enum { SMALL, BIG, SUPER } MarioState_t;

class Mario
{	
	// Mario properties
private:
	Clock timer1, timer2;
	float MarioAcceleration[2], MarioSpeed[2];
	bool GoRight, GoUp, GoLeft, GoDown, Jumping;
	float StartJumpPosition;

public:
	Texture MarioTexture;
	Sprite MarioSprite;
	MarioState_t MarioState;
	
	
	// Constractor
	Mario();

	// set Mario to small state
	void SmallState();

	// Move mario
	void Move();

	void CatchEvents(Event& event);

private:
	// Make animation for mario while walking
	void SetMarioRectForWalk(IntRect& intRect);

	// Make mario animation stand still 
	void StandStill();

	// make mario jump
	void Jump(IntRect& intRect, int RectPosition, float waiting);

	// make mario walk to the right
	void MoveRight(IntRect& intRect);

	// make mario walk to the left
	void MoveLeft(IntRect& intRect);
};

