// "SPACE DANCE" Game is a project at AUT - CE | Date : Jan - 2024 | Developer : Mohammad Javad Akbari 40231005

#define SDL_MAIN_HANDLED
#include "menu.h"
#include "gameLoop.h"
#include "essentials.h"

SDL_Rect ScreenRect = {0, 0, WIDTH, HEIGHT};
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int isMenuActive = FALSE, isGameActive = FALSE, LastTick;

int init();

void ShutDown();

int main() {
    atexit(ShutDown);
    isMenuActive = init();

    // main loop to run the game
    setupMenu();
    while (isMenuActive) {
        RenderMenu();
        processMenu();

        // GameLoop and frame rate controller
        while (isMenuActive && isGameActive) {
            renderGame();
            processGame();
            updateGame();

            int wait = FRAME_TIME - (SDL_GetTicks() - LastTick);
            if (wait > 0 && wait <= FRAME_TIME) SDL_Delay(wait);
            LastTick = SDL_GetTicks();
        }
    }

    return 0;
}

int init() {
    TTF_Init();
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "window error");
        return FALSE;
    }

    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "window error");
        return FALSE;
    }

    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "window error");
        return FALSE;
    }

    window = SDL_CreateWindow(
            "Space Dance",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH,
            HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "window error");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        fprintf(stderr, "render error");
        return FALSE;
    }

    return TRUE;
}

void ShutDown() {
    if (tmpMSGT != NULL) SDL_DestroyTexture(tmpMSGT);
    if (tmpMSGS != NULL) SDL_FreeSurface(tmpMSGS);

    if (GameBGT != NULL) SDL_DestroyTexture(GameBGT);
    if (GameBGS != NULL) SDL_FreeSurface(GameBGS);

    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    if (window != NULL) SDL_DestroyWindow(window);

    TTF_CloseFont(mFont);
    TTF_Quit();
    SDL_Quit();
}
