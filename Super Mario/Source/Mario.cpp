#include "../Header/Mario.h"


Mario::Mario(float x, float y) {
	// Init Mario motion varible
	acceleration[0] = 57;
	acceleration[1] = 120;
	speed[0] = 0;
	speed[1] = 70;
	startJumpPosition = 500;
	powerUpCounter = 0;
	goRight = goUp = goLeft = goDown = jumping = onGround = false;
	PoweringUpToSuper = PoweringUpToBig = false;

	// Set Mario Sprite Properties
	if(!marioTexture.loadFromFile(MARIO_CHARACTER)) { std::cout << "Can't load MARIO_CHARACTER\n"; }
	if (!marioSuperTexture.loadFromFile(MARIO_SUPER_CHARACTER)) { std::cout << "Can't load MARIO_SUPER_CHARACTER\n"; }
	marioTexture.setSmooth(true);
	marioSprite.setTexture(marioTexture); 	
	marioSprite.setPosition(x, y);
	marioSprite.setScale(2, 2);
	smallState();
}


void Mario::draw(RenderWindow& window) {
	window.draw(marioSprite);

	animation();
}


void Mario::animation() {
	move();
	changeToBig();
	changeToSuper();
}


void Mario::smallState() {
	marioSprite.setTexture(marioTexture);
	marioState = SMALL;
	marioArea.width = 28;
	marioArea.height = 32;
	marioSprite.setTextureRect(IntRect(0, 96, marioArea.width, marioArea.height));
	marioSprite.setOrigin(marioArea.width / 2, marioArea.height);
}


void Mario::bigState() {
	marioSprite.setTexture(marioTexture);
	marioState = BIG;
	marioArea.width = 31;
	marioArea.height = 60;
	marioSprite.setTextureRect(IntRect(0, 36, marioArea.width, marioArea.height));
	marioSprite.setOrigin(marioArea.width / 2, marioArea.height);
}


void Mario::superState() {
	bigState();
	marioState = SUPER;
	marioSprite.setTexture(marioSuperTexture);
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

	if (onGround) jumping = false;
	IntRect marioRect = marioSprite.getTextureRect();

	// used timer to make motion slower
	float waitingTime = 0.05; // 0.12s to make whole round
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
				speed[1] = -60;
				jumping = true;
			}
			goUp = false;
			onGround = false;
		}
		jump(marioRect, jumpRectPosition, waitingTime);

		waitingTime += 0.07;
		if (timer2.getElapsedTime().asSeconds() > waitingTime) {
			
			if (goRight) { // Move to right
				moveRight(marioRect);
			}

			else if (goLeft) { // Move to left
				moveLeft(marioRect);
			}
			else {
				// acceleration movement when release keyboard
				if (speed[0] >= 1 || speed[0] <= -1) {
					setMarioRectForWalk(marioRect);
					if(!jumping) marioSprite.setTextureRect(marioRect);

					// Calculate Mario Speed - X axis
					speed[0] = speed[0] + acceleration[0] * waitingTime;
				}
			}

			// set down when press arrow down
			if (goDown && marioState != SMALL) {

				goDown = false;
			}

			timer2.restart();
		}
		
		marioSprite.move(speed[0], speed[1]);

		timer1.restart();
	}

	if (speed[0] < 1 && speed[0] > -1 && onGround) {
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
	speed[0] = 0;
	switch (marioState)
	{
	case SMALL:
		smallState();
		break;
	case BIG:
		bigState();
		break;
	case SUPER:
		superState();
		break;
	default:
		break;
	}
}


void Mario::jump(IntRect& intRect, int RectPosition, float waiting) {
	if (onGround) {
		speed[1] = 0;
		jumping = false;
	} else {
		if (speed[1] > 0)
			acceleration[1] = 200;
		else
			acceleration[1] = 120;

		// Calculate Mario Speed - Y axis
		speed[1] = speed[1] + acceleration[1] * waiting;
	}
}


void Mario::moveRight(IntRect& intRect) {
	// check turnAround
	if (speed[0] <= -1) {
		intRect.left = 129; // Big and Super position
		if (marioState == SMALL) intRect.left = 132; // Small Position	
	}
	else {
		setMarioRectForWalk(intRect);
	}

	if (!jumping) marioSprite.setTextureRect(intRect);
	marioSprite.setScale(2, 2);

	speed[0] = 21;

	// Make acceleration work in the opposite side
	if (acceleration[0] > 0) acceleration[0] *= -1;
}


void Mario::moveLeft(IntRect& intRect) {
	// check turnAround
	if (speed[0] >= 1) {
		intRect.left = 129; // Big and Super position
		if (marioState == SMALL) intRect.left = 132; // Small Position	
	}
	else {
		setMarioRectForWalk(intRect);
	}

	if(!jumping) marioSprite.setTextureRect(intRect);
	marioSprite.setScale(-2, 2);

	speed[0] = -21;

	// Make acceleration work in the oppsite side
	if (acceleration[0] < 0) acceleration[0] *= -1;
}


void Mario::changeToBig() {
	if (PoweringUpToBig) {
		if (powerUpCounter < 12) { // The last one will be 11 (odd)
			if (powerUpTimer.getElapsedTime().asSeconds() > 0.18) {
				if (powerUpCounter % 2 == 0)
					smallState();
				else 
					bigState();

				powerUpCounter++;
				powerUpTimer.restart();
			}
		}
		else {
			powerUpCounter = 0;
			PoweringUpToBig = false;
		}
	}
}


void Mario::changeToSuper() {
	if (PoweringUpToSuper) {
		if (powerUpCounter < 12) { // The last one will be 11 (odd)
			if (powerUpTimer.getElapsedTime().asSeconds() > 0.18) {
				if (powerUpCounter % 2 == 0)
					smallState();
				else
					superState();

				powerUpCounter++;
				powerUpTimer.restart();
			}
		}
		else {
			powerUpCounter = 0;
			PoweringUpToSuper = false;
		}
	}
}


