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
    // Camera settings
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    UpdateCamera(&camera, CAMERA_FREE);

    // Start window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Load cube, its texture, and its shader
    Model cube = LoadModel("assets/Models/TestModel.obj");
    Texture2D texture = LoadTexture("assets/Textures/TestTexture.png");
    SetMaterialTexture(&cube.materials[0], MATERIAL_MAP_DIFFUSE, texture);
    Shader flatShader = LoadShader("assets/Shaders/flat.vs", "assets/Shaders/flat.fs");

    Vector3 cubePosition = (Vector3){0,0,0};

    //SetLighting(ColorToInt(WHITE), Vector3Zero(), 0, 0);

    //LoadLevel();

    int five = LEVEL_SIZE;
    printf("%i", five);

    while (!WindowShouldClose())
    {
        // Draw loop
        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode3D(camera);
        //DrawModel(cube, cubePosition, 1, WHITE);
        //DrawLevel();
        EndMode3D();
        EndDrawing();
    }

    // Unloading
    //UnloadLevel();
    UnloadTexture(texture);
    UnloadModel(cube);

    CloseWindow();

    return 0;
}
