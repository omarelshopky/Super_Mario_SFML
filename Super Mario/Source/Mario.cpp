#include "../Header/Mario.h"

#include <iostream>

Mario::Mario() {
	// Init Mario motion varible
	MarioAcceleration[0] = 25;
	MarioAcceleration[1] = 75;
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
	IntRect MarioRect = MarioSprite.getTextureRect();

	// used timer to make motion slower
	float waitingTime = 0.08; // 0.12
	if (timer1.getElapsedTime().asSeconds() > waitingTime)
	{
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
		Jump(MarioRect, jumpRectPosition, waitingTime);

		waitingTime += 0.04;
		if (timer2.getElapsedTime().asSeconds() > waitingTime) {
			
			if (GoRight) { // Move to right
				MoveRight(MarioRect);
			}

			else if (GoLeft) { // Move to left
				MoveLeft(MarioRect);
			}
			else {
				if (MarioSpeed[0] >= 1 || MarioSpeed[0] <= -1) {
					SetMarioRectForWalk(MarioRect);
					if(!Jumping)
						MarioSprite.setTextureRect(MarioRect);

					// Calculate Mario Speed - X axis
					MarioSpeed[0] = MarioSpeed[0] + MarioAcceleration[0] * waitingTime;
				}
			}

			// set down when press arrow down
			if (GoDown && MarioState != SMALL) {


			}

			timer2.restart();
		}
		
		
		MarioSprite.move(MarioSpeed[0], MarioSpeed[1]);

		timer1.restart();
	}

	if (MarioSpeed[0] < 1 && MarioSpeed[0] > -1 && (MarioSpeed[1] == 0 && !Jumping)) {
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


void Mario::Jump(IntRect& intRect, int RectPosition, float waiting) {
	if (Jumping) {
		if (MarioSpeed[1] <= -1) {
			intRect.left = RectPosition;
			MarioSprite.setTextureRect(intRect);
			// Calculate Mario Speed - Y axis
			MarioSpeed[1] = MarioSpeed[1] + MarioAcceleration[1] * waiting;
		}
		else {
			if (MarioSprite.getPosition().y < StartJumpPosition) {
				intRect.left = RectPosition;
				MarioSprite.setTextureRect(intRect);

				// Calculate Mario Speed - Y axis
				MarioSpeed[1] = MarioSpeed[1] + MarioAcceleration[1] * waiting;

			}
			if (MarioSprite.getPosition().y == StartJumpPosition) {
				Jumping = false;
				MarioSpeed[1] = 0;
			}
		}
	}
}


void Mario::MoveRight(IntRect& intRect) {
	// check turnAround
	if (MarioSpeed[0] <= -1) {
		intRect.left = 132;
	}
	else {
		if (!Jumping)
			SetMarioRectForWalk(intRect);
	}

	MarioSprite.setTextureRect(intRect);
	MarioSprite.setScale(2, 2);

	MarioSpeed[0] = 21;

	// Make acceleration work in the opposite side
	if (MarioAcceleration[0] > 0) {
		MarioAcceleration[0] *= -1;
	}
}

void Mario::MoveLeft(IntRect& intRect) {
	// check turnAround
	if (MarioSpeed[0] >= 1) {
		intRect.left = 132;
	}
	else {
		if (!Jumping)
			SetMarioRectForWalk(intRect);
	}

	MarioSprite.setTextureRect(intRect);
	MarioSprite.setScale(-2, 2);

	MarioSpeed[0] = -21;

	// Make acceleration work in the oppsite side
	if (MarioAcceleration[0] < 0) {
		MarioAcceleration[0] *= -1;
	}
}