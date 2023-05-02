#ifndef LEVEL_GEN_H
#define LEVEL_GEN_H

#define LEVEL_SIZE 11

int LoadLevelAssets(int levelNumber);
int DrawLevelAssets(void);
int UnloadLevelAssets(void);
static int GetRoadTextureIDAt(int row, int col);
const int(*GetCurrentLevelData())[LEVEL_SIZE];
void LoadLevelData(int levelNumber);


#endif