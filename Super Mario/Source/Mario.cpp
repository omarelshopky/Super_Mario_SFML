#include "../Header/Mario.h"

Mario::Mario() {
	// Init Mario motion varible
	Mario_XAcceleration = 0;
	Mario_YAcceleration = -9.8f;
	Mario_XSpeed = 0;
	Mario_YSpeed = 0;
	
	Mario_Texture.loadFromFile("Resource/Textures/Mario.png");
	Mario_Texture.setSmooth(true);
	Mario_Sprite.setTexture(Mario_Texture);
	Mario_Sprite.setPosition(300, 500);
	Mario_Sprite.setScale(2, 2);
	Small_State();
}


void Mario::Small_State() {
	MarioState = SMALL;
	int Height = 32;
	int Width = 28;
	Mario_Sprite.setTextureRect(IntRect(0, 96, Width, Height));
	Mario_Sprite.setOrigin(Height / 2, Width / 2);
}


void Mario::Move() {
	// used timer to make motion slower
	if (timer.getElapsedTime().asSeconds() > 0.06)
	{
		IntRect Mario_Rect = Mario_Sprite.getTextureRect();

		Mario_Sprite.move(Mario_XSpeed, 0);
		// Move to right
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			setMarioRectForWalk(Mario_Rect);
			Mario_Sprite.setTextureRect(Mario_Rect);
			Mario_Sprite.setScale(2, 2);
			Mario_XSpeed = 15;
			

		}
		else {

		}
		// Move to left
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			setMarioRectForWalk(Mario_Rect);
			Mario_Sprite.setTextureRect(Mario_Rect);
			Mario_Sprite.setScale(-2, 2);
			Mario_XSpeed = -15;
		}

		// Jump when press arrow up
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			Mario_Sprite.setScale(-2, 2);
			Mario_Sprite.move(-15, 0);
		}

		// set down when press arrow down
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			Mario_Sprite.setScale(-2, 2);
			Mario_Sprite.move(-15, 0);
		}
		
		timer.restart();
	}

	StandStill();
}

void Mario::setMarioRectForWalk(IntRect& intRect) {
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

	if (intRect.left == MaxLeft) 
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
	if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right))
	{
		Mario_XSpeed = 0;

		if (MarioState == SMALL)
		{
			Small_State();
		}
		else if (MarioState == BIG || MarioState == SUPER)
		{

		}
		else {/* Do Nothing */ }
	}
}