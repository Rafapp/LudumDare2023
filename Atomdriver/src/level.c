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

// Unloads current level and loads a new random level 
void LevelLoad(void)
{
	if(currentLevel != NULL)
		UnloadLevelAssets();

	// insert random generation here ---- 

	// ------

	LoadLevelAssets();
	currentLevel = GetCurrentLevelData();
	levelFinished = 0;
	startTime = GetTime();
	totalTimeSpent = 0;
}

// Unloads current level
void LevelUnload(void)
{
	UnloadLevelAssets();
	currentLevel = NULL;
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

// Updates timer and returns timer value
float ProcessLevelTimer()
{
	if (levelFinished)
		return totalTimeSpent;
	else
		return totalTimeSpent += GetFrameTime();
}

// Returns unformated time
float GetCurrentLevelTime(void)
{
	return totalTimeSpent;
}

// Call this one player reaches the finish point
void FinishedPointReached(void)
{
	levelFinished = 1;
}