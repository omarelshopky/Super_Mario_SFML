#pragma once
#include "../Header/DEFINITION.h"

class Mario
{	
	/***		Mario properties		***/
private:
	int changeStateCounter;
	Clock timer1, timer2, changeStateTimer;
	bool goRight, goUp, goLeft, goDown, damaging;
	float acceleration[2], startJumpPosition;
	area marioArea;
	SoundBuffer jumpBuffer, damageBuffer, dieBuffer;
	Sound jumpSound, damageSound, dieSound;

public:
	Texture marioTexture, marioSuperTexture;
	bool jumping, onGround, PoweringUpToBig, PoweringUpToSuper, dying, stuck, dead;
	float speed[2];
	Sprite marioSprite;
	marioState_t marioState;
	
	
	Mario(float x, float y); // Constractor

	/***			Methods			***/

	// Draw mario on screen 
	void draw(RenderWindow& window);


	// Handle events for mario movement
	void catchEvents(Event& event);


	// Start Damage animation
	void startDamage();


	// Start Die Animation
	void startDie();

private:
	// set Mario to small state
	void smallState();


	// set Mario to Big state
	void bigState();


	// set Mario to Super state
	void superState();


	// Mario movement animation
	void move();


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


	// Make animation for Mario changing
	void animation();


	// make animation for Power up to Big state
	void changeToBig();


	// make animation for Power up to Super state
	void changeToSuper();


	// Animation of converting mario from big or super state to small 
	void damage();


	// Animation of Dying
	void die();
};

