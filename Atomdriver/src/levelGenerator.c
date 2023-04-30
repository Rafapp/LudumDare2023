// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

// Script Headers
#include "levelGenerator.h"

// C headers
#include <stdio.h>

// 0 = road
// 1 = building
// 2 = start
// 3 = end
const int level[LEVEL_SIZE][LEVEL_SIZE] = {
    {2,0,0,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,0,1,1,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,0,1,0,1,1,0,1,1},
    {0,1,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,1,1,0,1,1},
    {0,1,1,0,0,0,0,0,0,3},
    {0,1,1,0,1,1,0,1,1,1},
    {0,0,0,0,0,0,0,1,1,1},
};

Model loadedModels[LEVEL_SIZE * LEVEL_SIZE];

const int tileSize = 1;

Texture2D roadTextureHor;
Texture2D roadTextureVer;
Texture2D roadTextureInt;
Texture2D buildingTexture_1;
Texture2D buildingTexture_2;
Texture2D buildingTexture_3;
Texture2D buildingTexture_Start;
Texture2D buildingTexture_End;

// Uses level[][] to as grid and loads models at each node
int LoadLevel(void)
{
    printf("-------- start loading level -----------");
    
#if defined(PLATFORM_WEB)
    roadTextureHor = LoadTexture("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Textures/Texture_Road_Horizontal_v2.png");
    roadTextureVer = LoadTexture("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Textures/Texture_Road_Vertical_v2.png");
    roadTextureInt = LoadTexture("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Textures/Texture_Road_Cross_v2.png");
    buildingTexture_1 = LoadTexture("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Textures/Texture_Building_1_v2.png");
    buildingTexture_2 = LoadTexture("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Textures/Texture_Building_2_v2.png");
    buildingTexture_3 = LoadTexture("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Textures/Texture_Building_3_v2.png");
    buildingTexture_Start = LoadTexture("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Textures/Texture_Building_Start_v2.png");
    buildingTexture_End = LoadTexture("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Textures/Texture_Building_End_v2.png");
#else
    roadTextureHor = LoadTexture("assets/Textures/Texture_Road_Horizontal_v2.png");
    roadTextureVer = LoadTexture("assets/Textures/Texture_Road_Vertical_v2.png");
    roadTextureInt = LoadTexture("assets/Textures/Texture_Road_Cross_v2.png");
    buildingTexture_1 = LoadTexture("assets/Textures/Texture_Building_1_v2.png");
    buildingTexture_2 = LoadTexture("assets/Textures/Texture_Building_2_v2.png");
    buildingTexture_3 = LoadTexture("assets/Textures/Texture_Building_3_v2.png");
    buildingTexture_Start = LoadTexture("assets/Textures/Texture_Building_Start_v2.png");
    buildingTexture_End = LoadTexture("assets/Textures/Texture_Building_End_v2.png");
#endif

    int model = 0;

    for (int col = 0; col < LEVEL_SIZE; col++)
    {
        for (int row = 0; row < LEVEL_SIZE; row++)
        {
            if (level[row][col] == 1) // load building
            {

                int totalBuildingVariations = 3;
                int variation = GetRandomValue(1, totalBuildingVariations);

                //variation = -1;
                switch (variation) // choose a building variation at random
                {
                case 1:
                    #if defined(PLATFORM_WEB)
                    loadedModels[model] = LoadModel("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Models/Model_Building_v1.obj");
                    #else
                    loadedModels[model] = LoadModel("assets/Models/Model_Building_v1.obj");
                    #endif
                    loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = buildingTexture_1;
                    break;
                case 2:
#if defined(PLATFORM_WEB)
                    loadedModels[model] = LoadModel("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Models/Model_Building_v2.obj");
#else
                    loadedModels[model] = LoadModel("assets/Models/Model_Building_v2.obj");
#endif
                    loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = buildingTexture_2;
                    break;
                case 3:
#if defined(PLATFORM_WEB)
                    loadedModels[model] = LoadModel("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Models/Model_Building_v3.obj");
#else
                    loadedModels[model] = LoadModel("assets/Models/Model_Building_v3.obj");
#endif
                    loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = buildingTexture_3;
                    break;
                default:
#if defined(PLATFORM_WEB)
                    loadedModels[model] = LoadModel("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Models/Model_Building_v1.obj"); // can this be cached? 
#else
                    loadedModels[model] = LoadModel("assets/Models/Model_Building_v1.obj");
#endif
                    loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = buildingTexture_1;
                    break;
                }

            }
            else if (level[row][col] == 2)
            {
#if defined(PLATFORM_WEB)
                loadedModels[model] = LoadModel("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Models/Model_Building_Start.obj");
#else
                loadedModels[model] = LoadModel("assets/Models/Model_Building_Start.obj");
#endif
                loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = buildingTexture_Start;
            }
            else if (level[row][col] == 3)
            {
#if defined(PLATFORM_WEB)
                loadedModels[model] = LoadModel("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Models/Model_Building_End.obj");
#else
                loadedModels[model] = LoadModel("assets/Models/Model_Building_End.obj");
#endif
                
                loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = buildingTexture_End;
            }
            else { // load a road

#if defined(PLATFORM_WEB)
                loadedModels[model] = LoadModel("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Models/M_Ludem_Tile_Road_V2.obj");
#else
                loadedModels[model] = LoadModel("assets/Models/M_Ludem_Tile_Road_V2.obj");
#endif
                              
                int type = GetRoadTextureIDAt(row, col);
                
                switch (type)
                {
                case 1: // See GetRoadTextureIDAt() for ID labels  
                    loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = roadTextureVer;        
                    break;
                case 2:
                    loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = roadTextureHor;
                    break;
                case 3:
                    loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = roadTextureInt;
                    break;
                default:
                    loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = roadTextureInt;
                    break;
                }                             
            }
            model++;
        }
    }
    printf("-------- end loading level ------------");
    return 0;
}

// Returns correct road texture ID by checking adjcent tiles
static int GetRoadTextureIDAt(int row, int col)
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

    
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };

    int adjcentTiles[4]; // N, E, S, W ... clockwise (maybe I should use MACROs)

    // get all adjcent tiles
    for (int i = 0; i < 4; i++) {
        int tileX = row + dx[i];
        int tileY = col + dy[i];

        if (tileX < 0 || tileY < 0 || tileX >= LEVEL_SIZE || tileY >= LEVEL_SIZE) // out of bounds
            adjcentTiles[i] = 1;
        else
            adjcentTiles[i] = level[tileX][tileY];
    }

    // not perfect but will do the job for now
    // Check for all the possible cases.....
    if (adjcentTiles[1] == 1 && adjcentTiles[3] == 1)
        return 1; // vertical
    if (adjcentTiles[0] == 1 && adjcentTiles[2] == 1)
        return 2; // horizontal
    if (adjcentTiles[0] == 0 && adjcentTiles[1] == 0 && adjcentTiles[2] == 0 && adjcentTiles[3] == 0)
        return 3; // intersection

    return 0;
}

// Loops through all models and draws them
int DrawLevel(void)
{
    // check for loaded first? Would be nice if this had error handling

    int model = 0;

    Vector3 offset = { 0.0f, 0.0f, 0.0f };
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

// Unloads all textures and models that were used
int UnloadLevel(void)
{
    UnloadTexture(buildingTexture_End);
    UnloadTexture(buildingTexture_Start);
    UnloadTexture(buildingTexture_3);
    UnloadTexture(buildingTexture_2);
    UnloadTexture(buildingTexture_1);


    UnloadTexture(roadTextureInt);
    UnloadTexture(roadTextureVer);
    UnloadTexture(roadTextureHor);

    for (int model = 0; model < LEVEL_SIZE * LEVEL_SIZE; model++)
    {
        //Model* modelToUnload = ;
        //loadedModels[model] = NULL; // hm how do I empty this array

        UnloadModel(loadedModels[model++]);

    }

    return 0;
}

const int(*GetCurrentLevelData())[LEVEL_SIZE] {
    return level;
}
