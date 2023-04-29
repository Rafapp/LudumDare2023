#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "levelGenerator.h"
#include <stdio.h>

// Window specs
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)
#define WINDOW_TITLE "Atomdriver"

int main(void)
{
    // Scale
    float scale = 15;

    // Camera settings
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 20.0f, 20.0f, 20.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;
    UpdateCamera(&camera, CAMERA_FREE);

    // Start window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Load cube and its texture
    Model cube = LoadModel("assets/Models/TestModel.obj");
    Texture2D texture = LoadTexture("assets/Textures/TestTexture.png");
    cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    Vector3 cubePosition = (Vector3){0,0,0};

    // Skybox
    Color topColor = {10, 63, 68, 255};
    Color bottomColor = {67, 153, 114};

    LoadLevel();
    // Movement
    Vector3 moveHorizontal = (Vector3){scale/2,0,0};
    Vector3 moveVertical = (Vector3){0,0,scale/2};

    while (!WindowShouldClose())
    {
        // Standard draw loop
        BeginDrawing();
            ClearBackground(topColor);
            BeginMode3D(camera);
                DrawModel(cube, cubePosition, scale, WHITE);
            EndMode3D();
        EndDrawing();

        // Input
        if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
            cubePosition = Vector3Add(cubePosition, Vector3Negate(moveVertical));
        }
        if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
            cubePosition = Vector3Add(cubePosition, Vector3Negate(moveHorizontal));
        }
        if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
            cubePosition = Vector3Add(cubePosition, moveVertical);
        }
        if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
            cubePosition = Vector3Add(cubePosition, moveHorizontal);
        }
    }

    // Unloading
    //UnloadLevel();
    UnloadTexture(texture);
    UnloadModel(cube);

    CloseWindow();

    return 0;
}
