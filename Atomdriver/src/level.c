// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "stdio.h"

// Script headers
#include "levelGenerator.h"
#include "level.h"

const int(*currentLevel)[LEVEL_SIZE] = NULL;

// Needs to be called when a new level is created
void LevelInit(void)
{
	currentLevel = GetCurrentLevelData();
}

int CheckForCollisions(Vector3* actorPosition)
{
	if (actorPosition == NULL) {
		return -1;
	}

	int x = (int)(actorPosition)->x;
	int y = (int)(actorPosition)->z;
	
	if (x < 0 || y < 0 || x >= LEVEL_SIZE || y >= LEVEL_SIZE) // out of bounds
		return 1;
	else
		return currentLevel[x][y];
}