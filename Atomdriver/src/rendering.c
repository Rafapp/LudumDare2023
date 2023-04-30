// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "stdio.h"
#include <string.h>

// Script headers
#include "game.h"
#include "rendering.h"
#include "levelGenerator.h"
#include "level.h"

// Window specs
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define WINDOW_TITLE "Atomdriver"

// Camera
Camera3D camera = { 0 };
float angle;

// Rendering variables
int scaleUnit = 1;

// Skybox
Color topColor = { 0, 105, 170, 1 };
Color bottomColor = {67, 153, 114};

// Objects and textures
Model truckModel;
Texture2D truckTexture;

// Initialize rendering variables
void RenderInit(){
    // Create a window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    LoadLevel(); // should be done by level.c


    // Camera settings
    camera.position = (Vector3){ 50.0f, 50.0f, 50.0f };
    camera.target = (Vector3){ 5.0f, 0.0f, 5.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 10.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    // Load cube and its texture
    truckModel = LoadModel("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Models/Truck.obj");
    truckTexture = LoadTexture("/Volumes/RAFASSD/PersonalProjects/LudumDare2023/Atomdriver/assets/Textures/TruckTexture.png");

    truckModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = truckTexture;
}

// For objects to be rendered every frame (Dynamic)
void RenderLoop(){
    // Standard draw loop
    BeginDrawing();
        ClearBackground(topColor);
        BeginMode3D(camera);
            DrawModel(truckModel, truckPosition, scaleUnit, WHITE);
            DrawLevel();           
        EndMode3D();
        RenderTimer();
    EndDrawing();
}

void RenderTimer(void)
{
    char timerLabel[] = "Timer: ";
    char str[50];
    char result[100]; // Make sure the array is large enough to hold the concatenated string

    snprintf(str, sizeof(str), "%.5f", GetCurrentLevelTime());
    snprintf(result, sizeof(result), "%s%s", timerLabel, str);

    DrawText(result, 10, 10, 20, WHITE);
}

// Unload all models and textures, close window
void Unload(){
    UnloadTexture(truckTexture);
    UnloadModel(truckModel);

    UnloadLevel();  // should be done by level.c

    CloseWindow();
}

