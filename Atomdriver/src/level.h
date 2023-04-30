#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

#define LEVEL_SIZE 10

void LevelInit(void);
int CheckForCollisions(Vector3* actorPosition);


#endif