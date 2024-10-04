#include "gameLoop.h"

// GameLoop Essentials
int EnemyCount, score, ShownScore, shownHealth, shownLevel, MaxEnemy, timer;
float cameraSpeed;

SDL_Surface *JetSurface, *MineSurface, *BomberSurface, *DroneSurface, *FighterSurface,
        *ShipSurface, *bombSurface, *bulletUpSurface, *explodeSurface, *healthSurface;
SDL_Texture *JetTexture, *MineTexture, *BomberTexture, *DroneTexture, *FighterTexture,
        *ShipTexture, *bombTexture, *bulletUpTexture, *explodeTexture, *healthTexture;

#define MAX_VECTOR 20
struct {
    int bulletLevel;
    int Health;
    int lastShot;
    SDL_Rect JetBulletRect[MAX_VECTOR];
    int JetBulletActive[MAX_VECTOR];
    SDL_Rect JetRect;
} Jet;
enemyStruct *EnemyHead;
int lastDrop;


void loadBmp() {
    JetSurface = SDL_LoadBMP(JET_PP);
    SDL_SetColorKey(JetSurface, SDL_TRUE, SDL_MapRGB(JetSurface->format, 0, 0, 0));
    JetTexture = SDL_CreateTextureFromSurface(renderer, JetSurface);

    MineSurface = SDL_LoadBMP(MINE_PP);
    SDL_SetColorKey(MineSurface, SDL_TRUE, SDL_MapRGB(MineSurface->format, 0, 0, 0));
    MineTexture = SDL_CreateTextureFromSurface(renderer, MineSurface);

    BomberSurface = SDL_LoadBMP(BOMBER_PP);
    SDL_SetColorKey(BomberSurface, SDL_TRUE, SDL_MapRGB(BomberSurface->format, 0, 0, 0));
    BomberTexture = SDL_CreateTextureFromSurface(renderer, BomberSurface);

    DroneSurface = SDL_LoadBMP(DRONE_PP);
    SDL_SetColorKey(DroneSurface, SDL_TRUE, SDL_MapRGB(DroneSurface->format, 0, 0, 0));
    DroneTexture = SDL_CreateTextureFromSurface(renderer, DroneSurface);

    FighterSurface = SDL_LoadBMP(FIGHTER_PP);
    SDL_SetColorKey(FighterSurface, SDL_TRUE, SDL_MapRGB(FighterSurface->format, 0, 0, 0));
    FighterTexture = SDL_CreateTextureFromSurface(renderer, FighterSurface);

    ShipSurface = SDL_LoadBMP(SHIP_PP);
    SDL_SetColorKey(ShipSurface, SDL_TRUE, SDL_MapRGB(ShipSurface->format, 0, 0, 0));
    ShipTexture = SDL_CreateTextureFromSurface(renderer, ShipSurface);

    bombSurface = SDL_LoadBMP(BOMB_PP);
    SDL_SetColorKey(bombSurface, SDL_TRUE, SDL_MapRGB(bombSurface->format, 0, 0, 0));
    bombTexture = SDL_CreateTextureFromSurface(renderer, bombSurface);

    healthSurface = SDL_LoadBMP(HEALTH_PP);
    SDL_SetColorKey(healthSurface, SDL_TRUE, SDL_MapRGB(healthSurface->format, 0, 0, 0));
    healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);

    bulletUpSurface = SDL_LoadBMP(BULLET_UP_PP);
    SDL_SetColorKey(bulletUpSurface, SDL_TRUE, SDL_MapRGB(bulletUpSurface->format, 0, 0, 0));
    bulletUpTexture = SDL_CreateTextureFromSurface(renderer, bulletUpSurface);

    explodeSurface = SDL_LoadBMP(EXPLODE_PP);
    SDL_SetColorKey(explodeSurface, SDL_TRUE, SDL_MapRGB(bulletUpSurface->format, 0, 0, 0));
    explodeTexture = SDL_CreateTextureFromSurface(renderer, explodeSurface);

    mFont = TTF_OpenFont(FONT_P, 100);
}

void setupGame() {
    if (!isGameActive) loadBmp();

    cameraSpeed = 2 * 60 / FPS;
    MaxEnemy = 10;
    EnemyCount = 0;

    isGameActive = TRUE;
    score = 0;
    ShownScore = score;
    EnemyHead = NULL;

    Jet.bulletLevel = 1;
    shownLevel = Jet.bulletLevel;
    Jet.Health = 5;
    shownHealth = Jet.Health;
    Jet.lastShot = 0;
    Jet.JetRect.x = WIDTH / 2 - 70 / 2;
    Jet.JetRect.y = HEIGHT - 180;
    Jet.JetRect.w = 70;
    Jet.JetRect.h = 100;

    for (int i = 0; i < MAX_VECTOR; i++) {
        Jet.JetBulletActive[i] = FALSE;
        Jet.JetBulletRect[i].w = 3;
        Jet.JetBulletRect[i].h = 10;
    }

    timer = SDL_GetTicks();
}

void renderGame() {
    clearRenderer();

    enemyStruct *current = EnemyHead;
    while (current != NULL) {
        if (current->type == bomberT) {
            if (current->health > 0)
                SDL_RenderCopy(renderer, BomberTexture, NULL, &current->enemyRect);
            if (current->attach)
                SDL_RenderCopy(renderer, bombTexture, NULL, &current->attachRect);
        }
        current = current->next;
    }

    current = EnemyHead;
    while (current != NULL) {
        if (current->type == explodeT) {
            if (current->health > 0)
                SDL_RenderCopy(renderer, explodeTexture, NULL, &current->enemyRect);
        }
        current = current->next;
    }

    current = EnemyHead;
    while (current != NULL) {
        switch (current->type) {
            case mineT:
                if (current->health > 0)
                    SDL_RenderCopy(renderer, MineTexture, NULL, &current->enemyRect);
                break;
            case droneT:
                if (current->health > 0)
                    SDL_RenderCopy(renderer, DroneTexture, NULL, &current->enemyRect);
                break;
            case fighterT:
                if (current->health > 0)
                    SDL_RenderCopy(renderer, FighterTexture, NULL, &current->enemyRect);

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                if (current->attach) SDL_RenderFillRect(renderer, &current->attachRect);
                break;
            case shipT:
                if (current->attach == 1)
                    SDL_RenderCopy(renderer, healthTexture, NULL, &current->attachRect);
                else if (current->attach == 2)
                    SDL_RenderCopy(renderer, bulletUpTexture, NULL, &current->attachRect);
                else if (current->health > 0)
                    SDL_RenderCopy(renderer, ShipTexture, NULL, &current->enemyRect);
                break;
            default:
                break;
        }
        current = current->next;
    }

    for (int i = 0; i < MAX_VECTOR; i++) {
        if (Jet.JetBulletActive[i]) {
            if (Jet.JetBulletActive[i] == 1)
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            else if (Jet.JetBulletActive[i] == 2)
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            else
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

            SDL_RenderFillRect(renderer, &Jet.JetBulletRect[i]);
        }
    }

    SDL_RenderCopy(renderer, JetTexture, NULL, &Jet.JetRect);

    SDL_Rect tmpMSGRect = {0, 0, WIDTH, 45};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &tmpMSGRect);

    tmpMSGRect.w = WIDTH;
    tmpMSGRect.h = 4;
    tmpMSGRect.x = 0;
    tmpMSGRect.y = 46;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &tmpMSGRect);

    tmpMSGRect.w = WIDTH * 3 / 4;
    tmpMSGRect.h = 35;
    tmpMSGRect.x = WIDTH / 2 - tmpMSGRect.w / 2;
    tmpMSGRect.y = 10;
    if (++score >= ShownScore + 50 || shownHealth != Jet.Health || shownLevel != Jet.bulletLevel || ShownScore == 0) {
        if (score >= ShownScore + 50) ShownScore = score;
        if (shownHealth != Jet.Health) shownHealth = Jet.Health;
        if (shownLevel != Jet.bulletLevel) shownLevel = Jet.bulletLevel;

        char tmpText[50] = {0};
        sprintf(tmpText, "Score : %d      Health : %d      Bullet Level : %d", ShownScore, shownHealth, shownLevel);
        renderMSG(tmpText, &tmpMSGRect, &White);
    } else
        SDL_RenderCopy(renderer, tmpMSGT, NULL, &tmpMSGRect);

    SDL_RenderPresent(renderer);
}

void processGame() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT)
            isMenuActive = FALSE;
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    ShowGameOver();
                    break;
                case SDLK_LEFT:
                    if (Jet.JetRect.x > 10) {
                        Jet.JetRect.x -= 10;
                    }
                    break;
                case SDLK_RIGHT:
                    if (Jet.JetRect.x + Jet.JetRect.w < WIDTH - 10) {
                        Jet.JetRect.x += 10;
                    }
                    break;
                case SDLK_UP:
                    if (Jet.JetRect.y > 200) {
                        Jet.JetRect.y -= 10;
                    }
                    break;
                case SDLK_DOWN:
                    if (Jet.JetRect.y < HEIGHT - 150) {
                        Jet.JetRect.y += 10;
                    }
                    break;
                case SDLK_SPACE:
                    if (SDL_GetTicks() - Jet.lastShot < 100) continue;
                    Jet.lastShot = SDL_GetTicks();
                    for (int i = 0; i < MAX_VECTOR; i++) {
                        if (!Jet.JetBulletActive[i]) {
                            Jet.JetBulletActive[i] = Jet.bulletLevel;
                            Jet.JetBulletRect[i].x = Jet.JetRect.x + (Jet.JetRect.w / 2) - (Jet.JetBulletRect[i].w / 2);
                            Jet.JetBulletRect[i].y = Jet.JetRect.y;
                            break;
                        }
                    }
                    break;
            }
        }
    }
}

void SpawnEnemy() {
    if (EnemyCount > MaxEnemy) return;

    srand(SDL_GetTicks());
    int randSpawn = rand() % 50;
    switch (randSpawn) {
        case mineT:
            dropMine();
            break;
        case droneT:
            dropDrone();
            break;
        case bomberT:
            dropBomber();
            break;
        case fighterT:
            dropFighter();
            break;
        case shipT:
            dropShip();
            break;
    }
}

int isPositionValid(int tmpX, int width) {
    enemyStruct *current = EnemyHead;
    while (current != NULL) {
        if (current->type == droneT || current->type == bomberT) {
            current = current->next;
            continue;
        }

        if (tmpX < width || tmpX > WIDTH - width) return FALSE;

        if (current->enemyRect.x >= tmpX) {
            if (current->enemyRect.x - tmpX < width) return FALSE;
        } else {
            if (tmpX - current->enemyRect.x < current->enemyRect.w) return FALSE;
        }
        current = current->next;
    }

    return TRUE;
}

int randPosition(int width) {
    int tmpX = rand() % (WIDTH - width);
    int prevX = tmpX;

    if (isPositionValid(tmpX, width))
        return tmpX;
    else {
        while (!isPositionValid(tmpX, width)) {
            tmpX += 10;
            if (tmpX > WIDTH - width) tmpX -= (WIDTH - width);
            if (tmpX == prevX) return -1 * width;
        }
        return tmpX;
    }
}

void dropExplode(enemyStruct *dead) {
    if (dead->health == -10) return;
    enemyStruct *newEnemy = addEnemyNode();
    newEnemy->type = explodeT;

    newEnemy->enemyRect.w = 40;
    newEnemy->enemyRect.h = 40;
    newEnemy->enemyRect.x = dead->enemyRect.x + (dead->enemyRect.w - 40) / 2;
    newEnemy->enemyRect.y = dead->enemyRect.y + (dead->enemyRect.h - 40) / 2;

    dead->health = -10;
    newEnemy->health = FPS / 2; // 0.5 sec
    newEnemy->attach = FALSE;
    EnemyCount++;
}

void dropMine() {
    int xPos = randPosition(30);
    enemyStruct *newEnemy = addEnemyNode();
    newEnemy->type = mineT;

    newEnemy->enemyRect.w = 30;
    newEnemy->enemyRect.h = 30;
    newEnemy->enemyRect.x = xPos;
    newEnemy->enemyRect.y = 0;

    newEnemy->health = 1;
    newEnemy->attach = FALSE;
    EnemyCount++;
}

void dropDrone() {
    if (SDL_GetTicks() - lastDrop < 1000) return;

    int xPos = randPosition(30);
    enemyStruct *newEnemy = addEnemyNode();
    newEnemy->type = droneT;

    newEnemy->enemyRect.w = 30;
    newEnemy->enemyRect.h = 70;
    newEnemy->enemyRect.x = xPos;
    newEnemy->enemyRect.y = 0;

    newEnemy->health = 2;
    newEnemy->attach = FALSE;
    EnemyCount++;
    lastDrop = SDL_GetTicks();
}

void dropBomber() {
    if (SDL_GetTicks() - lastDrop < 1000) return;

    enemyStruct *newEnemy = addEnemyNode();
    newEnemy->type = bomberT;

    newEnemy->enemyRect.w = 100;
    newEnemy->enemyRect.h = 50;
    newEnemy->enemyRect.x = WIDTH - 100;
    newEnemy->enemyRect.y = 0;

    newEnemy->attachRect.w = 8;
    newEnemy->attachRect.h = 32;
    newEnemy->health = 3;
    newEnemy->attach = FALSE;

    EnemyCount++;
    lastDrop = SDL_GetTicks();
}

void dropFighter() {
    if (SDL_GetTicks() - lastDrop < 1000) return;

    int xPos = randPosition(50);
    enemyStruct *newEnemy = addEnemyNode();
    newEnemy->type = fighterT;

    newEnemy->enemyRect.w = 50;
    newEnemy->enemyRect.h = 80;
    newEnemy->enemyRect.x = xPos;
    newEnemy->enemyRect.y = 0;

    newEnemy->attachRect.w = 3;
    newEnemy->attachRect.h = 10;
    newEnemy->health = 3;
    newEnemy->attach = FALSE;

    EnemyCount++;
    lastDrop = SDL_GetTicks();
}

void dropShip() {
    if (SDL_GetTicks() - lastDrop < 1000) return;

    int xPos = randPosition(50);
    enemyStruct *newEnemy = addEnemyNode();
    newEnemy->type = shipT;

    newEnemy->enemyRect.w = 50;
    newEnemy->enemyRect.h = 50;
    newEnemy->enemyRect.x = xPos;
    newEnemy->enemyRect.y = 0;

    newEnemy->attachRect.w = 30;
    newEnemy->attachRect.h = 30;
    newEnemy->health = 2;
    newEnemy->attach = FALSE;

    EnemyCount++;
    lastDrop = SDL_GetTicks();
}

void updateGame() {
    if (ShownScore > 10000) {
        cameraSpeed = 2 * 60 / FPS + 1;
        MaxEnemy = 15;
    } else if (ShownScore > 8000) {
        cameraSpeed = 2 * 60 / FPS + 0.8;
        MaxEnemy = 14;
    } else if (ShownScore > 6000) {
        cameraSpeed = 2 * 60 / FPS + 0.6;
        MaxEnemy = 13;
    } else if (ShownScore > 4000) {
        cameraSpeed = 2 * 60 / FPS + 0.4;
        MaxEnemy = 12;
    } else if (ShownScore > 2000) {
        cameraSpeed = 2 * 60 / FPS + 0.2;
        MaxEnemy = 11;
    }

    SpawnEnemy();

    for (int i = 0; i < MAX_VECTOR; i++) {
        if (Jet.JetBulletActive[i]) {
            Jet.JetBulletRect[i].y -= 4 * cameraSpeed;
            if (Jet.JetBulletRect[i].y <= 0) {
                Jet.JetBulletActive[i] = FALSE;
            }
        }
    }

    enemyStruct *current = EnemyHead;
    while (current != NULL) {

        for (int i = 0; i < MAX_VECTOR; i++) {
            if (current->type != explodeT && current->type != bomberT && Jet.JetBulletActive[i] &&
                current->health > 0) {
                if (SDL_HasIntersection(&Jet.JetBulletRect[i], &current->enemyRect)) {
                    current->health -= Jet.bulletLevel;
                    Jet.JetBulletActive[i] = FALSE;
                }
            }
            if (current->type != shipT && current->attach &&
                SDL_HasIntersection(&Jet.JetBulletRect[i], &current->attachRect)) {
                current->attach = FALSE;
                Jet.JetBulletActive[i] = FALSE;
            }
        }

        switch (current->type) {
            case mineT:
                updateMine(current);
                break;
            case droneT:
                updateDrone(current);
                break;
            case bomberT:
                updateBomber(current);
                break;
            case fighterT:
                updateFighter(current);
                break;
            case shipT:
                updateShip(current);
                break;
            case explodeT:
                updateExplode(current);
                break;
        }
        if (current->type != explodeT && current->health <= 0) dropExplode(current);

        if ((current->enemyRect.y >= HEIGHT || current->health <= 0) && current->attach <= 0) {
            EnemyCount--;
            enemyStruct *dead = current;
            current = current->next;
            delNode(dead);
            continue;
        }
        if (Jet.Health < 0) Jet.Health = 0;
        if (Jet.Health > 10) Jet.Health = 10;
        if (Jet.bulletLevel > 3) Jet.bulletLevel = 3;
        if (Jet.bulletLevel < 1) Jet.bulletLevel = 0;
        if (Jet.bulletLevel <= 0) Jet.Health = 0;

        if (Jet.Health <= 0) ShowGameOver();

        if (EnemyHead == NULL) break;
        current = current->next;
    }
}

void updateExplode(enemyStruct *current) {
    current->enemyRect.y += cameraSpeed;
    current->health -= 1;
}

void updateMine(enemyStruct *current) {
    current->enemyRect.y += cameraSpeed;
    if (SDL_HasIntersection(&Jet.JetRect, &current->enemyRect)) {
        current->health = 0;
        Jet.Health -= 1;
        Jet.bulletLevel -= 1;
    }
}

void updateFighter(enemyStruct *current) {
    current->enemyRect.y += 2.5 * cameraSpeed;

    if (current->health > 0 && SDL_HasIntersection(&Jet.JetRect, &current->enemyRect)) {
        current->health = 0;
        Jet.Health -= 3;
        Jet.bulletLevel -= 1;
    }
    if (current->attach && SDL_HasIntersection(&Jet.JetRect, &current->attachRect)) {
        Jet.Health -= 1;
        current->attach = FALSE;
    }
    if (rand() % 50 == 1 && current->attach <= 0 && current->health > 0) {
        current->attach = TRUE;
        current->attachRect.y = current->enemyRect.y + current->enemyRect.h;
        current->attachRect.x = current->enemyRect.x + current->enemyRect.w / 2;
    } else if (current->attach) {
        current->attachRect.y += cameraSpeed * 4;
        if (current->attachRect.y >= HEIGHT) current->attach = FALSE;
    }
}

void updateBomber(enemyStruct *current) {
    if (current->health > 0) {
        current->enemyRect.x -= cameraSpeed;
        current->enemyRect.y += cameraSpeed;
    }

    if (current->attach && SDL_HasIntersection(&Jet.JetRect, &current->attachRect)) {
        Jet.Health -= 2;
        current->attach = FALSE;
    }

    if (rand() % 50 == 1 && current->attach <= 0 && current->health > 0) {
        current->attach = TRUE;
        current->attachRect.y = current->enemyRect.y + current->enemyRect.h;
        current->attachRect.x = current->enemyRect.x + current->enemyRect.w / 2;
    } else if (current->attach) {
        current->attachRect.y += 3 * cameraSpeed;
        if (current->attachRect.y >= HEIGHT) current->attach = FALSE;
    }

    if (current->attach > 0) {
        enemyStruct *tmp = EnemyHead;
        while (tmp != NULL) {
            if (tmp->type == bomberT || tmp->type == explodeT || tmp == current) {
                tmp = tmp->next;
                continue;
            }
            if (tmp->health > 0 && SDL_HasIntersection(&tmp->enemyRect, &current->attachRect)) {
                tmp->health = 0;
                current->attach = FALSE;
            }
            tmp = tmp->next;
        }
    }
}

void updateShip(enemyStruct *current) {
    if (current->health > 0) current->enemyRect.y += cameraSpeed * 2;

    if (current->health > 0 && SDL_HasIntersection(&Jet.JetRect, &current->enemyRect)) {
        current->health = 0;
        Jet.Health -= 2;
    }

    if (current->health <= 0 && current->attach == FALSE) {
        current->attach = rand() % 2 + 1;
        current->attachRect.y = current->enemyRect.y + current->enemyRect.h / 2;
        current->attachRect.x = current->enemyRect.x + current->enemyRect.w / 2;
    }
    if (current->health <= 0 && current->attach != FALSE) {
        current->attachRect.y += cameraSpeed;
        if (current->attachRect.y >= HEIGHT) current->attach = FALSE;
    }

    if (current->health <= 0 && current->attach >= 0 && SDL_HasIntersection(&Jet.JetRect, &current->attachRect)) {
        if (current->attach == 1) // health
            Jet.Health += 2;
        else if (current->attach == 2) // bullet up
            Jet.bulletLevel += 1;

        current->attach = 0;
    }
}

void updateDrone(enemyStruct *current) {
    current->enemyRect.y += 2 * cameraSpeed;
    if (SDL_HasIntersection(&Jet.JetRect, &current->enemyRect)) {
        current->health = 0;
        Jet.Health -= 3;
        Jet.bulletLevel -= 1;
    }

    if (current->enemyRect.y > Jet.JetRect.y + Jet.JetRect.h + 10) return;
    if (current->enemyRect.x > Jet.JetRect.x + Jet.JetRect.w / 2)
        current->enemyRect.x -= 1;
    else if (current->enemyRect.x < Jet.JetRect.x + Jet.JetRect.w / 2)
        current->enemyRect.x += 1;

    if (current->health > 0) {
        enemyStruct *tmp = EnemyHead;
        while (tmp != NULL) {
            if (tmp->type == bomberT || tmp->type == explodeT || tmp == current) {
                tmp = tmp->next;
                continue;
            }
            if (tmp->health > 0 && SDL_HasIntersection(&tmp->enemyRect, &current->enemyRect)) {
                current->health = 0;
                tmp->health = 0;
            }
            if (tmp->type == fighterT && tmp->attach >= 0 && tmp->health > 0 &&
                SDL_HasIntersection(&tmp->attachRect, &current->enemyRect)) {
                current->attach = 0;
                tmp->health = 0;
            }
            tmp = tmp->next;
        }
    }
}

enemyStruct *addEnemyNode() {
    enemyStruct *newEnemy = (enemyStruct *) malloc(sizeof(struct node));
    if (newEnemy == NULL) {
        fprintf(stderr, "memory error");
        exit(-1);
    }
    newEnemy->next = NULL;

    if (EnemyHead == NULL) {
        EnemyHead = newEnemy;
    } else {
        enemyStruct *current = EnemyHead;
        while (current->next != NULL) current = current->next;
        current->next = newEnemy;
    }

    return newEnemy;
}

void freeNodes() {
    while (EnemyHead != NULL) {
        enemyStruct *tmp = EnemyHead;
        EnemyHead = EnemyHead->next;
        free(tmp);
    }
}

void delNode(enemyStruct *dead) {
    if (dead == EnemyHead) {
        EnemyHead = EnemyHead->next;
        free(dead);
    } else {
        enemyStruct *current = EnemyHead;
        while (current->next != dead) current = current->next;
        current->next = dead->next;
        free(dead);
    }
}

void storeLogs() {
    clearRenderer();
    SDL_Rect rect = {WIDTH / 2 - 200, HEIGHT / 2 - 100, 400, 50};
    char tmpText[50] = {0};
    sprintf(tmpText, "Game Over !    Score : %d", ShownScore);

    SDL_Rect tmpRect = {WIDTH / 2 - 75, HEIGHT / 2 + 100, 150, 30}, cursor = {WIDTH / 2 + 78, HEIGHT / 2 + 100, 3, 30};
    SDL_StartTextInput();
    char message[40] = "Enter a username : "; // 19 chars

    SDL_Event event;
    int done = FALSE, i = 19;
    while (TRUE) {
        clearRenderer();

        renderMSG(tmpText, &rect, &Blue);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        renderMSG(message, &tmpRect, &White);
        SDL_RenderFillRect(renderer, &cursor);
        SDL_RenderPresent(renderer);

        if (done) break;
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                done = TRUE;
                isGameActive = FALSE;
                isMenuActive = FALSE;
                exit(0);
            case SDL_TEXTINPUT:
                if (i < 39) {
                    strcat(message, event.edit.text);
                    i++;
                    tmpRect.x -= 5;
                    tmpRect.w += 12;
                    cursor.x = tmpRect.x + tmpRect.w + 3;
                }
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN) {
                    done = TRUE;
                } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    if (i > 19) {
                        message[--i] = 0;
                        tmpRect.x += 5;
                        tmpRect.w -= 12;
                        cursor.x = tmpRect.x + tmpRect.w + 3;
                    }
                }
        }
    }
    SDL_StopTextInput();


    FILE *list = fopen(LIST_P, "ab");
    if (list == NULL) list = fopen(LIST_P, "wb");
    if (list == NULL) {
        fprintf(stderr, "file error");
        exit(-1);
    }

    char result[100] = {0};
    time_t playTime = time(NULL);
    sprintf(result, "Name : %-20.20s Score : %-6dDate : %-24.24s  seconds played : %-4d", message + 19, ShownScore,
            ctime(&playTime), timer); // 27 + 15 + 32 + 23 -> 42,55
    fwrite(result, 97, 1, list);
    fclose(list);
}

void ShowGameOver() {
    timer = (SDL_GetTicks() - timer) / 1000;
    freeNodes();

    storeLogs();

    secondMenu();
    if (!isGameActive) terminateGame();
}

void terminateGame() {
    if (JetTexture != NULL) SDL_DestroyTexture(JetTexture);
    if (JetSurface != NULL) SDL_FreeSurface(JetSurface);

    if (MineTexture != NULL) SDL_DestroyTexture(MineTexture);
    if (MineSurface != NULL) SDL_FreeSurface(MineSurface);

    if (BomberTexture != NULL) SDL_DestroyTexture(BomberTexture);
    if (BomberSurface != NULL) SDL_FreeSurface(BomberSurface);

    if (DroneTexture != NULL) SDL_DestroyTexture(DroneTexture);
    if (DroneSurface != NULL) SDL_FreeSurface(DroneSurface);

    if (FighterTexture != NULL) SDL_DestroyTexture(FighterTexture);
    if (FighterSurface != NULL) SDL_FreeSurface(FighterSurface);

    if (ShipTexture != NULL) SDL_DestroyTexture(ShipTexture);
    if (ShipSurface != NULL) SDL_FreeSurface(ShipSurface);

    if (bombTexture != NULL) SDL_DestroyTexture(bombTexture);
    if (bombSurface != NULL) SDL_FreeSurface(bombSurface);

    if (bulletUpTexture != NULL) SDL_DestroyTexture(bulletUpTexture);
    if (bulletUpSurface != NULL) SDL_FreeSurface(bulletUpSurface);

    if (healthTexture != NULL) SDL_DestroyTexture(healthTexture);
    if (healthSurface != NULL) SDL_FreeSurface(healthSurface);
}