#include "menu.h"

// Menu pointer position
#define MPX (WIDTH / 2 - WIDTH / 3 / 2 - 100 - 20)
#define MPY (HEIGHT / 3 + 30 - 5)
#define MPM (90)

SDL_Rect MenuPointer1 = {MPX, MPY, 100, 5};
SDL_Rect MenuPointer2 = {MPX + 100 + WIDTH / 3 + 20 * 2 - 5, MPY, 100, 5};

// Type Material
SDL_Color White = {255, 255, 255};
SDL_Color Blue = {0, 255, 255};
TTF_Font *mFont = NULL;
SDL_Surface *tmpMSGS, *GameBGS;
SDL_Texture *tmpMSGT, *GameBGT;

void setupMenu() {
    mFont = TTF_OpenFont(FONT_P, 100);

    GameBGS = SDL_LoadBMP(GAME_BGP);
    GameBGT = SDL_CreateTextureFromSurface(renderer, GameBGS);
}

void RenderMenu() {
    clearRenderer();

    SDL_Rect tmpMSGRect = {WIDTH / 2 - (WIDTH * 2 / 3) / 2, HEIGHT / 8, WIDTH * 2 / 3, 100};
    char tmpText[40] = {0};
    sprintf(tmpText, "SPACE  DANCE");
    renderMSG(tmpText, &tmpMSGRect, &Blue);

    tmpMSGRect.w = WIDTH / 3;
    tmpMSGRect.h = 50;
    tmpMSGRect.x = WIDTH / 2 - tmpMSGRect.w / 2;
    for (int i = 0; i < 3; i++) setMenuOptions(i, &tmpMSGRect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &MenuPointer1);
    SDL_RenderFillRect(renderer, &MenuPointer2);

    tmpMSGRect.w = 380;
    tmpMSGRect.h = 18;
    tmpMSGRect.x = 10;
    tmpMSGRect.y = HEIGHT - 18 - 10;
    renderMSG("Keys : Esc, space, up, down, left, right", &tmpMSGRect, &White);

    tmpMSGRect.w = 120;
    tmpMSGRect.h = 18;
    tmpMSGRect.x = WIDTH - 120 - 10;
    tmpMSGRect.y = HEIGHT - 18 - 10;
    renderMSG("AUT University", &tmpMSGRect, &White);

    tmpMSGRect.w = 400;
    tmpMSGRect.h = 20;
    tmpMSGRect.x = WIDTH / 2 - 200;
    tmpMSGRect.y = HEIGHT * 4 / 5;
    renderMSG("Developed by mohammad Javad Akbari", &tmpMSGRect, &White);

    SDL_RenderPresent(renderer);
}

void setMenuOptions(int ind, SDL_Rect *tmpMSGRect) {
    char tmpText[40] = {0};
    tmpMSGRect->y = HEIGHT / 3 + ind * MPM;
    switch (ind) {
        case 0:
            sprintf(tmpText, "Play");
            break;
        case 1:
            sprintf(tmpText, "Logs");
            break;
        case 2:
            sprintf(tmpText, "Exit");
            break;
    }
    renderMSG(tmpText, tmpMSGRect, &White);
}

void processMenu() {
    SDL_Event event;
    SDL_WaitEvent(&event);

    if (event.type == SDL_QUIT)
        isMenuActive = FALSE;
    else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                isMenuActive = FALSE;
                exit(0);
            case SDLK_DOWN:
                if (MenuPointer1.y < MPY + 2 * MPM) {
                    MenuPointer1.y += MPM;
                    MenuPointer2.y += MPM;
                }
                break;
            case SDLK_UP:
                if (MenuPointer1.y > MPY) {
                    MenuPointer1.y -= MPM;
                    MenuPointer2.y -= MPM;
                }
                break;
            case SDLK_RETURN:
                if (MenuPointer1.y == MPY) {
                    setupGame();
                } else if (MenuPointer1.y == MPY + 1 * MPM) {
                    showScores();
                } else if (MenuPointer1.y == MPY + 2 * MPM) {
                    isMenuActive = FALSE;
                }
                break;
        }
    }
}

void showScores() {
    clearRenderer();

    SDL_Rect tmpMSGRect = {WIDTH / 10, HEIGHT / 10, 350, 30};
    renderMSG("Your Scores List", &tmpMSGRect, &White);

    tmpMSGRect.w = 420;
    tmpMSGRect.h = 20;
    tmpMSGRect.y += 50;
    tmpMSGRect.x += 50;

    FILE *list = fopen(LIST_P, "rb");
    if (list == NULL) {
        renderMSG("File is not found !", &tmpMSGRect, &Blue);
    } else {
        if (getc(list) == EOF){
            renderMSG("Empty            ", &tmpMSGRect, &Blue);
        }
        else {
            rewind(list);
            fseek(list, -97, SEEK_END);

            for (int i = 0; i <= (HEIGHT - 200) / 40 / 2; i++) {
                char tmpText[60] = {0};
                fread(tmpText, 42, 1, list);
                renderMSG(tmpText, &tmpMSGRect, &Blue);

                fread(tmpText, 55, 1, list);
                tmpMSGRect.y += 30;
                renderMSG(tmpText, &tmpMSGRect, &Blue);

                tmpMSGRect.y += 40;

                fseek(list, -194, SEEK_CUR);
                if (ftell(list) == SEEK_SET) i = (HEIGHT - 200) / 40 / 2 - 1;
            }
        }
    }

    if (list != NULL) fclose(list);
    SDL_RenderPresent(renderer);

    waitClick();
}

void secondMenu() {
    clearRenderer();

    SDL_Rect tmpRect1 = {WIDTH / 2 - 150, HEIGHT / 2 - 40, 300, 50};
    SDL_Rect tmpRect2 = {WIDTH / 2 - 175, HEIGHT / 2 + 40, 350, 50};
    SDL_Rect pointer1 = {WIDTH / 2 - 100 - 185, HEIGHT / 2 - 25, 100, 5};
    SDL_Rect pointer2 = {WIDTH / 2 + 185, HEIGHT / 2 - 25, 100, 5};

    SDL_Event event;
    int done = FALSE;
    while (TRUE) {
        clearRenderer();

        renderMSG("play again", &tmpRect1, &Blue);
        renderMSG("Return to Menu", &tmpRect2, &White);


        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderFillRect(renderer, &pointer1);
        SDL_RenderFillRect(renderer, &pointer2);
        SDL_RenderPresent(renderer);

        if (done) break;
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            done = TRUE;
            isGameActive = FALSE;
            isMenuActive = FALSE;
            exit(0);
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    isGameActive = FALSE;
                    done = TRUE;
                    break;
                case SDLK_DOWN:
                    if (pointer1.y < HEIGHT / 2) {
                        pointer1.y += 80;
                        pointer2.y += 80;
                    }
                    break;
                case SDLK_UP:
                    if (pointer1.y > HEIGHT / 2) {
                        pointer1.y -= 80;
                        pointer2.y -= 80;
                    }
                    break;
                case SDLK_RETURN:
                    if (pointer1.y > HEIGHT / 2) {
                        isGameActive = FALSE;
                    } else if (pointer1.y < HEIGHT / 2) {
                        isGameActive = TRUE;
                        setupGame();
                    }
                    done = TRUE;
                    break;
            }
        }
    }
}

void renderMSG(char *text, SDL_Rect *rect, SDL_Color *color) {
    tmpMSGS = TTF_RenderText_Solid(mFont, text, *color);
    tmpMSGT = SDL_CreateTextureFromSurface(renderer, tmpMSGS);
    SDL_RenderCopy(renderer, tmpMSGT, NULL, rect);
}

void clearRenderer() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, GameBGT, NULL, &ScreenRect);
}

void waitClick() {
    SDL_Event event;
    while (TRUE) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            isMenuActive = FALSE;
            isGameActive = FALSE;
            exit(0);
        } else if (event.type == SDL_KEYDOWN)
            break;
    }
}