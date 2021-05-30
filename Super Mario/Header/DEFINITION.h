#pragma once
/***		Include SFML files			***/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/***		Include Helper Libraries		***/
#include <windows.h>
#include<iostream>
#include <sstream>
#include<iomanip>
#include<fstream>
#include<map>
#include<string>


using namespace std;
using namespace sf;


/***			Special Variable			***/
typedef enum { SMALL, BIG, SUPER } marioState_t;


struct player {
	string name;
	string score;
	string level;
	int lifes;
};

struct area {
	float width;
	float height;
};

struct position {
	float x;
	float y;
};

/***						Menu						***/
#define MAIN_MENU_FONT "Resource/Fonts/Barkentina_font.ttf"

#define CAIRO_REGULAR "Resource/Fonts/Cairo-Regular.ttf"

#define MAIN_MENU_BACKGROUND "Resource/Textures/Menu/Menu.jpg"

#define PLAYER_NAME_BACKGROUND "Resource/Textures/Menu/playerName.jpg"

#define MENU_SHADOW "Resource/Textures/MenuShadow.png"

#define HIGH_SCORE_BACKGROUND "Resource/Textures/Menu/highScore.jpg"

#define HOW_TO_PLAY_BACKGROUND "Resource/Textures/Menu/howToPlay.jpg"

#define OPTIONS_BACKGROUND "Resource/Textures/Menu/Options.jpg"

#define CREDITS_BACKGROUND "Resource/Textures/Menu/Credits.jpg"

#define MUSIC_BALL "Resource/Textures/Menu/musicBall.png"

#define DIFFICULTY_BALL "Resource/Textures/Menu/difficultyBall.png"

#define CONTROL_BALL "Resource/Textures/Menu/controlBall.png"

#define MENU_SOUND "Resource/Music/MenuMusic.ogg"
/**********************************************************/




/***						Mario						***/
#define MARIO_CHARACTER "Resource/Textures/Mario.png"

/**********************************************************/




/***					GameEngine						***/
#define PLAYERS_FILE "Files/Players.txt"

#define GAME_HEADER_FONT "Resource/Fonts/some_font.ttf"

/**********************************************************/