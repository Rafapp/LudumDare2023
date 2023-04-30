// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "stdio.h"

// Script headers
#include "rendering.h"
#include "game.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


// Movement
Vector3 moveHorizontal = (Vector3){1.0f,0,0};
Vector3 moveVertical = (Vector3){0,0,1.0f};
Vector3 rotationAxis = (Vector3){0, 1, 0};
Vector3 truckPosition = (Vector3){0,0,0};

// Separated into function for web support
void UpdateFunction(void){
    // Input
    if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
        truckPosition = Vector3Add(truckPosition, Vector3Negate(moveVertical));
        truckModel.transform = MatrixRotateXYZ((Vector3){ 0.0f, DEG2RAD * 0, 0.0f });
    }
    if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
        truckPosition = Vector3Add(truckPosition, Vector3Negate(moveHorizontal));
        truckModel.transform = MatrixRotateXYZ((Vector3){ 0.0f, DEG2RAD * 90, 0.0f });
    }
    if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
        truckPosition = Vector3Add(truckPosition, moveVertical);
        truckModel.transform = MatrixRotateXYZ((Vector3){ 0.0f, DEG2RAD * 180, 0.0f });
    }
    if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
        truckPosition = Vector3Add(truckPosition, moveHorizontal);
        truckModel.transform = MatrixRotateXYZ((Vector3){ 0.0f, DEG2RAD * 270, 0.0f });
    }

    RenderLoop();
}

int main(void)
{
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
    RenderInit();
    UpdateFunction();

    Unload();
    return 0;
}


