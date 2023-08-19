#ifndef RESOURCE_H
#define RESOURCE_H

#include "ltexture.h"
#include <iostream>

//Scene textures
extern LTexture gRedTexture;
extern LTexture gGreenTexture;
extern LTexture gBlueTexture;
extern LTexture gShimmerTexture;

//Particle count
static int const TOTAL_PARTICLES = 20;

//func
bool LoadMedia();

void UnLoadMedia();

#endif