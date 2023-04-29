#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "levelGenerator.h"
#include <stdio.h>


const int level[LEVEL_SIZE][LEVEL_SIZE] = {
    {0,1,0,1,0},
    {0,0,0,0,0},
    {0,1,0,1,0},
    {0,0,0,0,0},
    {0,1,0,1,0},
};

Model loadedModels[LEVEL_SIZE * LEVEL_SIZE];

const int tileSize = 1;

Texture2D texture;


int LoadLevel(void)
{
    printf("-------- start loading -----------");
    texture = LoadTexture("assets/Textures/TestTexture.png"); // Load model texture

    for (int model = 0; model < LEVEL_SIZE * LEVEL_SIZE; model++)
    {
            loadedModels[model] = LoadModel("assets/Models/TestModel.obj");
            loadedModels[model].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    }
    


    printf("-------- end loading ------------");
    return 0;
}

int DrawLevel(void)
{
    // check for loaded first?

    int model = 0;

    for (int col = 0; col < (LEVEL_SIZE * tileSize); col += tileSize) // does * have great priority than < ?
    {
        for (int row = 0; row < (LEVEL_SIZE * tileSize); row += tileSize)
        {
            Vector3 position = { row, 0, col }; // should these be floats? 
            DrawModel(loadedModels[model], position, 1.0f, WHITE);
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
}