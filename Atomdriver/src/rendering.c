// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "stdio.h"
#include "levelGenerator.h"

// Script headers
#include "game.h"
#include "rendering.h"

// Window specs
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)
#define WINDOW_TITLE "Atomdriver"

// Camera
Camera3D camera = { 0 };

// Rendering variables
int scaleUnit = 1;

// Skybox
Color topColor = {10, 63, 68, 255};
Color bottomColor = {67, 153, 114};

// Objects and textures
Model truckModel;
Texture2D truckTexture;

// Initialize rendering variables
void RenderInit(){
    // Create a window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Camera settings
    
    camera.position = (Vector3){ 20.0f, 20.0f, 20.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;
    // UpdateCamera(&camera, CAMERA_FREE);

    // Load cube and its texture
    truckModel = LoadModel("../assets/Models/Truck.obj");
    truckTexture = LoadTexture("../assets/Textures/truckTexture.png");
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
    EndDrawing();
}

// Unload all models and textures, close window
void Unload(){
    UnloadTexture(truckTexture);
    UnloadModel(truckModel);

    UnloadLevel();

    CloseWindow();
}

