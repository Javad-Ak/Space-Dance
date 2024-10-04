#ifndef SPACEDANCE_ESSENTIALS_H
#define SPACEDANCE_ESSENTIALS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define TRUE 1
#define FALSE 0
#define WIDTH 800 // 800x800 is default. Don't set lower than 600x600.
#define HEIGHT 800
#define FPS 60 // 60 fps is default. Don't set higher than 120.
#define FRAME_TIME (1000/FPS)

#define GAME_BGP "./src/resources/backGround.bmp"
#define FONT_P "./src/resources/LaFamilia.ttf"
#define LIST_P "./src/resources/scoresList.bin"

#define JET_PP "./src/resources/Jet.bmp"
#define MINE_PP "./src/resources/mine.bmp"
#define DRONE_PP "./src/resources/drone.bmp"
#define BOMB_PP "./src/resources/bomb.bmp"
#define BOMBER_PP "./src/resources/bomber.bmp"
#define FIGHTER_PP "./src/resources/fighter.bmp"
#define SHIP_PP "./src/resources/ship.bmp"
#define HEALTH_PP "./src/resources/health.bmp"
#define BULLET_UP_PP "./src/resources/bulletUp.bmp"
#define EXPLODE_PP "./src/resources/explode.bmp"

// General Essentials
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Rect ScreenRect;

extern int isMenuActive, isGameActive, LastTick;

// BackGround
extern SDL_Surface *GameBGS;
extern SDL_Texture *GameBGT;

// Type Material
extern SDL_Color White;
extern SDL_Color Blue;
extern TTF_Font *mFont;
extern SDL_Surface *tmpMSGS;
extern SDL_Texture *tmpMSGT;

#endif
