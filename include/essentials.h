#ifndef SPACEDANCE_ESSENTIALS_H
#define SPACEDANCE_ESSENTIALS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_image.h>

#define TRUE 1
#define FALSE 0
#define WIDTH 800 // 800x800 is default. Don't set lower than 600x600.
#define HEIGHT 800
#define FPS 60 // 60 fps is default. Don't set higher than 120.
#define FRAME_TIME (1000/FPS)

#define GAME_BGP "../assets/backGround.bmp"
#define FONT_P "../assets/LaFamilia.ttf"
#define LIST_P "../assets/scoresList.bin"
#define MUSIC_P "../assets/music.mp3"

#define JET_PP "../assets/Jet.bmp"
#define MINE_PP "../assets/mine.bmp"
#define DRONE_PP "../assets/drone.bmp"
#define BOMB_PP "../assets/bomb.bmp"
#define BOMBER_PP "../assets/bomber.bmp"
#define FIGHTER_PP "../assets/fighter.bmp"
#define SHIP_PP "../assets/ship.bmp"
#define HEALTH_PP "../assets/health.bmp"
#define BULLET_UP_PP "../assets/bulletUp.bmp"
#define EXPLODE_PP "../assets/explode.bmp"

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
