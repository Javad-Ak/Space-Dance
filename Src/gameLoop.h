#ifndef SPACEDANCE_GAMELOOP_H
#define SPACEDANCE_GAMELOOP_H

#include "./Essentials.h"
#include "./menu.h"

// enemy essentials
enum enemyType {
    bomberT, fighterT, shipT, mineT, droneT, explodeT
};
typedef struct node {
    struct node *next;
    enum enemyType type;
    SDL_Rect enemyRect;
    SDL_Rect attachRect;
    int attach;
    int health;
} enemyStruct;

void loadBmp();

void setupGame();

void renderGame();

void processGame();

void updateGame();


void updateMine(enemyStruct *current);

void updateDrone(enemyStruct *current);

void updateBomber(enemyStruct *current);

void updateFighter(enemyStruct *current);

void updateShip(enemyStruct *current);

void updateExplode(enemyStruct *current);


void SpawnEnemy();

int isPositionValid(int tmpX, int width);

int randPosition(int width);

void dropExplode(enemyStruct *current);

void dropShip();

void dropFighter();

void dropBomber();

void dropDrone();

void dropMine();


enemyStruct *addEnemyNode();

void delNode(enemyStruct *dead);

void freeNodes();

void storeLogs();

void ShowGameOver();

void terminateGame();

#endif
