#include "../Header/Mario.h"

#include <iostream>

Mario::Mario() {
	// Init Mario motion varible
	MarioAcceleration[0] = 25;
	MarioAcceleration[1] = 50;
	MarioSpeed[0] = MarioSpeed[1] = 0;
	StartJumpPosition = 500;
	GoRight = GoUp = GoLeft = GoDown = Jumping = false;

	MarioTexture.loadFromFile("Resource/Textures/Mario.png");
	MarioTexture.setSmooth(true);
	MarioSprite.setTexture(MarioTexture);
	MarioSprite.setPosition(300, 500);
	MarioSprite.setScale(2, 2);
	SmallState();
}


void Mario::SmallState() {
	MarioState = SMALL;
	int Height = 32;
	int Width = 28;
	MarioSprite.setTextureRect(IntRect(0, 96, Width, Height));
	MarioSprite.setOrigin(Height / 2, Width / 2);
}


void Mario::CatchEvents() {
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		GoRight = true;
	}
	else {
		GoRight = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		GoLeft = true;
	}
	else {
		GoLeft = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		GoUp = true;
	}
	else {
		GoUp = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		GoDown = true;
	}
	else {
		GoDown = false;
	}
}


void Mario::Move() {
	// used timer to make motion slower
	float waitingTime = 0.12;
	if (timer.getElapsedTime().asSeconds() > waitingTime)
	{
		IntRect MarioRect = MarioSprite.getTextureRect();

		// Move to right
		if (GoRight) {
			// check turnAround
			if (MarioSpeed[0] <= -1) {
				MarioRect.left = 132;
			}
			else {
				SetMarioRectForWalk(MarioRect);	
			}

			MarioSprite.setTextureRect(MarioRect);
			MarioSprite.setScale(2, 2);

			MarioSpeed[0] = 21;
			

			// Make acceleration work in the opposite side
			if (MarioAcceleration[0] > 0) {
				MarioAcceleration[0] *= -1;
			}
			
		}
		
		// Move to left
		else if (GoLeft) {
			// check turnAround
			if (MarioSpeed[0] >= 1) {
				MarioRect.left = 132;
			}
			else {
				SetMarioRectForWalk(MarioRect);
			}

			MarioSprite.setTextureRect(MarioRect);
			MarioSprite.setScale(-2, 2);

			MarioSpeed[0] = -21;
			//MarioSprite.move(MarioSpeed[0], 0);

			// Make acceleration work in the oppsite side
			if (MarioAcceleration[0] < 0) {
				MarioAcceleration[0] *= -1;
			}
		}
		else {
			if (MarioSpeed[0] >= 1 || MarioSpeed[0] <= -1) {
				SetMarioRectForWalk(MarioRect);
				MarioSprite.setTextureRect(MarioRect);

				// Calculate Mario Speed - X axis
				MarioSpeed[0] = MarioSpeed[0] + MarioAcceleration[0] * waitingTime;
			}
		}

		// Jump when press arrow up
		int jumpRectPosition = 162.5;
		if (GoUp) {
			MarioRect.left = jumpRectPosition;
			MarioSprite.setTextureRect(MarioRect);
			if (Jumping == false) {
				StartJumpPosition = MarioSprite.getPosition().y;
				MarioSpeed[1] = -60;
				Jumping = true;
			}
		}
		if(Jumping){
			if (MarioSpeed[1] <= -1) {
				MarioRect.left = jumpRectPosition;
				MarioSprite.setTextureRect(MarioRect);
				// Calculate Mario Speed - Y axis
				MarioSpeed[1] = MarioSpeed[1] + MarioAcceleration[1] * waitingTime;
			}
			else {
				if (MarioSprite.getPosition().y < StartJumpPosition) {
					MarioRect.left = jumpRectPosition;
					MarioSprite.setTextureRect(MarioRect);

					// Calculate Mario Speed - Y axis
					MarioSpeed[1] = MarioSpeed[1] + MarioAcceleration[1] * waitingTime;

				}
				if (MarioSprite.getPosition().y == StartJumpPosition) {
					Jumping = false;
					MarioSpeed[1] = 0;
				}
			}
		}
		std::cout << MarioSprite.getPosition().y << ' ' << StartJumpPosition << '\n';
		// set down when press arrow down
		if (GoDown && MarioState != SMALL) {
			
			
		}
		
		MarioSprite.move(MarioSpeed[0], MarioSpeed[1]);

		timer.restart();
	}

	if (MarioSpeed[0] < 1 && MarioSpeed[0] > -1) {
		StandStill();
	}
	
	
}

void Mario::SetMarioRectForWalk(IntRect& intRect) {
	int MaxLeft = 0, PicWidth = 0;

	if (MarioState == SMALL)
	{
		MaxLeft = 99;
		PicWidth = 33;
	}
	else if (MarioState == BIG || MarioState == SUPER)
	{
		///////////////////////////////////////////////
	}
	else {/* Do Nothing */ }

	if (intRect.left >= MaxLeft)
	{
		intRect.left = PicWidth;
	}
	else 
	{
		intRect.left += PicWidth;
	}

	return;
}

void Mario::StandStill() {
	MarioSpeed[0] = 0;

	if (MarioState == SMALL)
	{
		SmallState();
	}
	else if (MarioState == BIG || MarioState == SUPER)
	{

	}
	else {/* Do Nothing */ }
}


