// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "stdio.h"

// Script headers
#include "levelGenerator.h"
#include "level.h"

const int(*currentLevel)[LEVEL_SIZE] = NULL;

float startTime;
float totalTimeSpent;

int levelFinished = 0;

// Needs to be called when a new level is created
void LevelInit(void)
{
	currentLevel = GetCurrentLevelData();
	levelFinished = 0;
	startTime = GetTime();
	totalTimeSpent = 0;
}

// Returns the tile ID at the given position
int CheckForCollisions(Vector3* position)
{
	if (position == NULL) {
		return -1;
	}

	int x = (int)(position)->x;
	int y = (int)(position)->z;
	
	if (x < 0 || y < 0 || x >= LEVEL_SIZE || y >= LEVEL_SIZE) // out of bounds
		return 1;
	else
		return currentLevel[x][y];
}

// returns unformated time
float ProcessLevelTimer()
{
	if (levelFinished)
		return totalTimeSpent;
	else
		return totalTimeSpent += GetFrameTime();
}

float GetCurrentLevelTime(void)
{
	return totalTimeSpent;
}

// Call this one player reaches the finish point
void FinishedPointReached(void)
{
	levelFinished = 1;
}