// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

// Script Headers
#include "levelGenerator.h"

// C headers
#include <stdio.h>

const int level[LEVEL_SIZE][LEVEL_SIZE] = {
    {0,1,0,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,0,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,0,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,0,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,0,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,0,0},
};

Model loadedModels[LEVEL_SIZE * LEVEL_SIZE];

const int tileSize = 1;

Texture2D texture;
Texture2D roadTextureHor;
Texture2D roadTextureVer;
Texture2D roadTextureInt;
Texture2D buildingTexture;

int LoadLevel(void)
{
    printf("-------- start loading level -----------");

    texture = LoadTexture("../assets/Textures/TestTexture.png"); // Load model texture

    roadTextureHor = LoadTexture("../assets/Textures/T_Tile_Road_v1.png");
    roadTextureVer = LoadTexture("../assets/Textures/T_Tile_Road_v1.png");
    roadTextureInt = LoadTexture("../assets/Textures/T_Tile_Road_v2.png");
    buildingTexture = LoadTexture("../assets/Textures/T_Tile_Building.png");

    int model = 0;

    for (int col = 0; col < LEVEL_SIZE; col++)
    {
        for (int row = 0; row < LEVEL_SIZE; row++)
        {
            if (level[row][col] == 1) // load building
            {
                loadedModels[model] = LoadModel("../assets/Models/M_Ludem_Tile_Building.obj");
                loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = buildingTexture;
            }
            else { // load a road
                loadedModels[model] = LoadModel("../assets/Models/M_Ludem_Tile_Road.obj");
                int type = GetRoadTypeAt(row, col);
                switch (type)
                {
                case 1:
                    loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = roadTextureVer;             
                default:
                    break;
                }
            }
            model++;
        }
    }
    printf("-------- end loading level ------------");
    return 0;
}

int GetRoadTypeAt(int row, int col)
{
    // 1: vertical
    // 2: horiztonal
    // 3: intersection
    // ---- unsupported ----
    // 4: t section north
    // 5: t section south
    // 6: t section west
    // 7: t section east
    // 8: L section north
    // 9: L section south
    // 10: L section west
    // 11: L section east

    /*
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    int adjcentTypes[4]; 

    for (int i = 0; i < 4; i++) {
        int newX = row + dx[i];
        int newY = col + dy[i];

        if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols) {
            printf("Tile (%d, %d) has value: %d\n", newX, newY, grid[newX][newY]);
        }
    }

    */
    return 1;
}

int DrawLevel(void)
{
    // check for loaded first?
    int model = 0;

    Vector3 offset = { -5.0f, 0.0f, -5.0f };
    for (int col = 0; col < (LEVEL_SIZE * tileSize); col += tileSize) // does * have great priority than < ?
    {
        for (int row = 0; row < (LEVEL_SIZE * tileSize); row += tileSize)
        {
            Vector3 position = { row, 0, col}; // should these be floats? 

            DrawModel(loadedModels[model], Vector3Add(position, offset), 1.0f, WHITE);
            model++;
        }
    }
    return 0;
}

int UnloadLevel(void)
{
    UnloadTexture(texture);

    for (int model = 0; model < LEVEL_SIZE * LEVEL_SIZE; model++)
    {
        //Model* modelToUnload = ;
        //loadedModels[model] = NULL; // hm how do I empty this array

        UnloadModel(loadedModels[model++]);

    }

    return 0;
}