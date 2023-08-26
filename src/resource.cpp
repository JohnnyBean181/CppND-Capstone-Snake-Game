#include "resource.h"

// global variable
LTexture gRedTexture;
LTexture gGreenTexture;
LTexture gBlueTexture;
LTexture gShimmerTexture;

//Globally used font
LTexture gTextTexture_1p;
LTexture gTextTexture_2p;
LTexture gTextTexture_pvc;
LTexture gTextTexture_exit;

// The protective mutex
SDL_mutex* gBufferLock = NULL;

// The conditions
SDL_cond* gCanProduce = NULL;
SDL_cond* gCanConsume = NULL;