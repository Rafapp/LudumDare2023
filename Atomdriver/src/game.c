// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "stdio.h"

// Script headers
#include "rendering.h"
#include "level.h"
#include "game.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// Movement
Vector3 moveHorizontal = (Vector3){1.0f, 0, 0};
Vector3 moveVertical = (Vector3){0, 0, 1.0f};
Vector3 rotationAxis = (Vector3){0, 1, 0};
Vector3 truckPosition = (Vector3){0, 0, 0};
Vector3 desiredPosition = (Vector3){0, 0, 0};
Matrix desiredTransform;

// Separated into function for web support
void UpdateFunction(void){
  ProcessLevelTimer();
    // Input
        if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
            desiredPosition = Vector3Add(truckPosition, Vector3Negate(moveVertical));
            desiredTransform = MatrixRotateXYZ((Vector3){ 0.0f, DEG2RAD * 0, 0.0f });
        }
        if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
            desiredPosition = Vector3Add(truckPosition, Vector3Negate(moveHorizontal));
            desiredTransform = MatrixRotateXYZ((Vector3){ 0.0f, DEG2RAD * 90, 0.0f });
        }
        if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
            desiredPosition = Vector3Add(truckPosition, moveVertical);
            desiredTransform = MatrixRotateXYZ((Vector3){ 0.0f, DEG2RAD * 180, 0.0f });
        }
        if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
            desiredPosition = Vector3Add(truckPosition, moveHorizontal);
            desiredTransform = MatrixRotateXYZ((Vector3){ 0.0f, DEG2RAD * 270, 0.0f });
        }

        int targetTile = CheckForCollisions(&desiredPosition);

        if (targetTile == 0)
        {
            truckPosition = desiredPosition;
            truckModel.transform = desiredTransform;
        }
        else if (targetTile == 3) // level finished
        {
            FinishedPointReached();
        }
        //printf("%i at (%f , %f)\n",c, truckPosition.x, truckPosition.z);

    RenderLoop();
}

int main(void)
{
    RenderInit();
    LevelInit(); // must go after render 
    desiredTransform = MatrixRotateXYZ((Vector3) { 0.0f, 0, 0.0f });

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateFunction, 0, 1);
    #else
        SetTargetFPS(60);   
        // Main game loop
        while (!WindowShouldClose())
        {
            UpdateFunction();
        }
    #endif
    
    Unload();
    return 0;
}


