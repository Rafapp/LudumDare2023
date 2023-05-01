#ifndef LEVEL_GEN_H
#define LEVEL_GEN_H

#define LEVEL_SIZE 10

int LoadLevelAssets(void);
int DrawLevelAssets(void);
int UnloadLevelAssets(void);
static int GetRoadTextureIDAt(int row, int col);
const int(*GetCurrentLevelData())[LEVEL_SIZE];


#endif