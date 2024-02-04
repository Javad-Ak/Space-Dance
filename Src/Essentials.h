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
#define WIDTH 800 // 800x800 is native. don't set lower than 600.
#define HEIGHT 800
#define FPS 60 // 60 is native. don't set higher than 120.
#define FRAME_TIME (1000/FPS)

#define GAME_BGP "./Src/Resources/backGround.bmp"
#define FONT_P "./Src/Resources/LaFamilia.ttf"
#define LIST_P "./Src/Resources/scoresList.bin"

#define JET_PP "./Src/Resources/Jet.bmp"
#define MINE_PP "./Src/Resources/mine.bmp"
#define DRONE_PP "./Src/Resources/drone.bmp"
#define BOMB_PP "./Src/Resources/bomb.bmp"
#define BOMBER_PP "./Src/Resources/bomber.bmp"
#define FIGHTER_PP "./Src/Resources/fighter.bmp"
#define SHIP_PP "./Src/Resources/ship.bmp"
#define HEALTH_PP "./Src/Resources/health.bmp"
#define BULLET_UP_PP "./Src/Resources/bulletUp.bmp"
#define EXPLODE_PP "./Src/Resources/explode.bmp"

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
