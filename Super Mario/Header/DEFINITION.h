#pragma once
/***		Include SFML files			***/
#include <SFML/Graphics.hpp>

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

// Make enum for mario state
typedef enum { SMALL, BIG, SUPER } marioState_t;


/***						Menu						***/
#define MAIN_MENU_FONT "Resource/Fonts/Barkentina_font.ttf"

#define PLAYER_NAME_FONT "Resource/Fonts/Cairo-Regular.ttf"

#define MAIN_MENU_BACKGROUND "Resource/Textures/Menu/Menu.jpg"

#define PLAYER_NAME_BACKGROUND "Resource/Textures/Menu/playerName.jpg"

#define MENU_SHADOW "Resource/Textures/MenuShadow.png"

/**********************************************************/




/***						Mario						***/
#define MARIO_CHARACTER "Resource/Textures/Mario.png"

/**********************************************************/




/***					GameEngine						***/
#define PLAYERS_FILE "Files/Players.txt"

#define GAME_HEADER_FONT "Resource/Fonts/some_font.ttf"

/**********************************************************/