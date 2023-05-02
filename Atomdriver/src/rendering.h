#ifndef RENDERER_H
#define RENDERER_H

// Raylib headers
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "stdio.h"

// Window specs
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define WINDOW_TITLE "Atomdriver"

extern int scaleUnit;
extern Model truckModel;

void RenderInit(void);
void RenderLoop(void);
void Unload(void);
void RenderTimer(void);

#endif