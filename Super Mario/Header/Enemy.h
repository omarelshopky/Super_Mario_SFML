#pragma once
#include "../Header/DEFINITION.h"
#include "../Header/GameEngine.h"

class Enemy
{
	/***			Properties				***/
private:
	GameEngine* gameEngine;
	Sprite* minX;
	Sprite* maxX;
	RectangleShape* ground;
	enemy_t enemyType;
	IntRect enemyRect, blackRect, smashedRect, turtleRect, shellRect;
	Text floatingText;
	Clock timer, textFloatTimer;
	int CurrentRect, maxRect, floatingSpeed, killScore;
	float speed[2];
	bool faid, isKilled, resetTime, moving, onGround, firstTime;

public:
	Sprite enemySprite;
	bool display;

	Enemy(GameEngine& gameEngine, enemy_t type, Sprite& minX, Sprite& maxX, RectangleShape& ground, float x, float y);


	/***			Methods				***/

	// Draw enemy on screen
	void draw(RenderWindow& window);

private:
	// handle animation for the enemy
	void animation();
	

	// Change direction of motion when face the bounds
	void changeDirection();

	
	// See if there is ground below the enemy
	void checkGround();


	// Text floating Up when kill the enemy
	void TextFloat();


	// Check If mario has Killed this enemy or not
	void checkKilled();


	// Handle what will happend when enemy is killed
	void setKilled();
};

