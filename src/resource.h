#ifndef RESOURCE_H
#define RESOURCE_H

#include "ltexture.h"

//Scene textures
extern LTexture gRedTexture;
extern LTexture gGreenTexture;
extern LTexture gBlueTexture;
extern LTexture gShimmerTexture;

//Rendered texture
extern LTexture gTextTexture_1p;
extern LTexture gTextTexture_2p;
extern LTexture gTextTexture_pvc;
extern LTexture gTextTexture_exit;

//Particle count
static int const TOTAL_PARTICLES = 20;
static int const kScreenWidth = 640;
static int const kScreenHeight = 640;

#endif