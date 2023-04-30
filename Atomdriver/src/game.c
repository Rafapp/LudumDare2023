// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "stdio.h"

// Script headers
#include "rendering.h"
#include "game.h"

Vector3 truckPosition;

int main(void)
{
    truckPosition = (Vector3){0,0,0};
    RenderInit();

    // Movement
    Vector3 moveHorizontal = (Vector3){scaleUnit/2,0,0};
    Vector3 moveVertical = (Vector3){0,0,scaleUnit/2};
    Vector3 rotationAxis = (Vector3){0, 1, 0};

    while (!WindowShouldClose())
    {
        RenderLoop();
        
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
    }

    Unload();
    return 0;
}
