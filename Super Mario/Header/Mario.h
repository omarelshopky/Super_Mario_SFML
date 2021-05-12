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
	float Mario_XAcceleration, Mario_YAcceleration;
	float Mario_XSpeed, Mario_YSpeed;

public:
	Texture Mario_Texture;
	Sprite Mario_Sprite;
	MarioState_t MarioState;
	
	
	// Constractor
	Mario();

	// set Mario to small state
	void Small_State();

	// Move mario
	void Move();

private:
	// Make animation for mario while walking
	void setMarioRectForWalk(IntRect& intRect);

	// Make mario animation stand still 
	void StandStill();

};

