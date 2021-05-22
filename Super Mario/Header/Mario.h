#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

// Make enum for mario state
typedef enum { SMALL, BIG, SUPER } MarioState_t;

class Mario
{	
	// Mario properties
private:
	Clock timer;
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

	void CatchEvents();

private:
	// Make animation for mario while walking
	void SetMarioRectForWalk(IntRect& intRect);

	// Make mario animation stand still 
	void StandStill();

	// Make animation for mario turn from right to left and vice versa
};

