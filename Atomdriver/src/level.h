#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

#define LEVEL_SIZE 10

void LevelInit(void);
int CheckForCollisions(Vector3* actorPosition);
float ProcessLevelTimer(void);
void FinishedPointReached(void);
float GetCurrentLevelTime(void);

#endif