#include "../Header/Mario.h"

Mario::Mario() {
	Mario_Texture.loadFromFile("Resource/Textures/Mario.png");
	Mario_Sprite.setTexture(Mario_Texture);
	Mario_Sprite.setPosition(100, 50);
	Mario_Sprite.setOrigin(50, 50);
};