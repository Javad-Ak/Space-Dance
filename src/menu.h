#ifndef SPACEDANCE_MENU_H
#define SPACEDANCE_MENU_H

#include "./gameLoop.h"
#include "./essentials.h"

void setupMenu();

void processMenu();

void setMenuOptions(int ind, SDL_Rect *tmpMSGRect);

void RenderMenu();

void showScores();

void secondMenu();

void renderMSG(char *text, SDL_Rect *rect, SDL_Color *color);

void clearRenderer();

void waitClick();

#endif
