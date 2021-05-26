#include "../Header/Mario.h"


Mario::Mario() {
	// Init Mario motion varible
	marioAcceleration[0] = 25;
	marioAcceleration[1] = 75;
	marioSpeed[0] = marioSpeed[1] = 0;
	startJumpPosition = 500;
	goRight = goUp = goLeft = goDown = jumping = false;

	marioTexture.loadFromFile("Resource/Textures/Mario.png");
	marioTexture.setSmooth(true);
	marioSprite.setTexture(marioTexture); 	
	marioSprite.setPosition(300, 500);
	marioSprite.setScale(2, 2);
	smallState();
}


void Mario::smallState() {
	marioState = SMALL;
	int Height = 32;
	int Width = 28;
	marioSprite.setTextureRect(IntRect(0, 96, Width, Height));
	marioSprite.setOrigin(Height / 2, Width / 2);
}


void Mario::bigState() {
	marioState = BIG;
	int Height = 60;
	int Width = 31;
	marioSprite.setTextureRect(IntRect(0, 36, Width, Height));
	marioSprite.setOrigin(Height / 2, Width / 2);
}


void Mario::catchEvents(Event& event) {
	switch (event.type) {
	case Event::KeyPressed:
		switch (event.key.code)
		{
		case Keyboard::Key::Right:
			goRight = true;
			break;
		
		case Keyboard::Key::Left:
			goLeft = true;
			break;

		case Keyboard::Key::Space:
			goUp = true;
			break;

		case Keyboard::Key::Down:
			goDown = true;
			break;
		}
		break;

	case Event::KeyReleased:
		switch (event.key.code)
		{
		case Keyboard::Key::Right:
			goRight = false;
			break;

		case Keyboard::Key::Left:
			goLeft = false;
			break;
		}
		break;
	}
}


void Mario::move() {
	IntRect marioRect = marioSprite.getTextureRect();

	// used timer to make motion slower
	float waitingTime = 0.08; // 0.12s to make whole round
	if (timer1.getElapsedTime().asSeconds() > waitingTime)
	{
		// Jump when press arrow up
		int jumpRectPosition = 161; // Big and Super position = 161
		if (marioState == SMALL) jumpRectPosition += 1.5; // Small position = 162.5

		if (goUp) {
			marioRect.left = jumpRectPosition;
			marioSprite.setTextureRect(marioRect);
			if (jumping == false) {
				startJumpPosition = marioSprite.getPosition().y;
				marioSpeed[1] = -60;
				jumping = true;
			}
			goUp = false;
		}
		jump(marioRect, jumpRectPosition, waitingTime);

		waitingTime += 0.04;
		if (timer2.getElapsedTime().asSeconds() > waitingTime) {
			
			if (goRight) { // Move to right
				moveRight(marioRect);
			}

			else if (goLeft) { // Move to left
				moveLeft(marioRect);
			}
			else {
				// acceleration movement when release keyboard
				if (marioSpeed[0] >= 1 || marioSpeed[0] <= -1) {
					setMarioRectForWalk(marioRect);
					if(!jumping) marioSprite.setTextureRect(marioRect);

					// Calculate Mario Speed - X axis
					marioSpeed[0] = marioSpeed[0] + marioAcceleration[0] * waitingTime;
				}
			}

			// set down when press arrow down
			if (goDown && marioState != SMALL) {

				goDown = false;
			}

			timer2.restart();
		}
		
		marioSprite.move(marioSpeed[0], marioSpeed[1]);

		timer1.restart();
	}

	if (marioSpeed[0] < 1 && marioSpeed[0] > -1 && (marioSpeed[1] == 0 && !jumping)) {
		standStill();
	}
}


void Mario::setMarioRectForWalk(IntRect& intRect) {
	int maxLeft = 0, picWidth = 0;

	if (marioState == SMALL)
	{
		maxLeft = 99;
		picWidth = 33;
	}
	else if (marioState == BIG || marioState == SUPER)
	{
		maxLeft = 96;
		picWidth = 32;
	}
	else {/* Do Nothing */ }

	if (intRect.left >= maxLeft)
	{
		intRect.left = picWidth;
	}
	else 
	{
		intRect.left += picWidth;
	}

	return;
}

void Mario::standStill() {
	marioSpeed[0] = 0;
	switch (marioState)
	{
	case SMALL:
		smallState();
		break;
	case BIG:
		bigState();
		break;
	case SUPER:

		break;
	default:
		break;
	}
}


void Mario::jump(IntRect& intRect, int RectPosition, float waiting) {
	if (jumping) {
		if (marioSprite.getPosition().y == startJumpPosition && marioSpeed[1] > -1) {
			jumping = false;
			marioSpeed[1] = 0;
		}
		else {
			intRect.left = RectPosition;
			marioSprite.setTextureRect(intRect);
			// Calculate Mario Speed - Y axis
			marioSpeed[1] = marioSpeed[1] + marioAcceleration[1] * waiting;
		}
	}
}


void Mario::moveRight(IntRect& intRect) {
	// check turnAround
	if (marioSpeed[0] <= -1) {
		intRect.left = 129; // Big and Super position
		if (marioState == SMALL) intRect.left = 132; // Small Position	
	}
	else {
		if (!jumping) setMarioRectForWalk(intRect);
	}

	marioSprite.setTextureRect(intRect);
	marioSprite.setScale(2, 2);

	marioSpeed[0] = 21;

	// Make acceleration work in the opposite side
	if (marioAcceleration[0] > 0) marioAcceleration[0] *= -1;
}


void Mario::moveLeft(IntRect& intRect) {
	// check turnAround
	if (marioSpeed[0] >= 1) {
		intRect.left = 129; // Big and Super position
		if (marioState == SMALL) intRect.left = 132; // Small Position	
	}
	else {
		if (!jumping) setMarioRectForWalk(intRect);
	}

	marioSprite.setTextureRect(intRect);
	marioSprite.setScale(-2, 2);

	marioSpeed[0] = -21;

	// Make acceleration work in the oppsite side
	if (marioAcceleration[0] < 0) marioAcceleration[0] *= -1;
}