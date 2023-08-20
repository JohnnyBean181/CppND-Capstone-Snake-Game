#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include <iostream>
#include "ltexture.h"
#include "resource.h"

class Particle
{
	public:
		//Initialize position and animation
		Particle( int x, int y);

		//Shows the particle
		void render(SDL_Renderer *sdl_renderer);

		//Checks if particle is dead
		bool isDead();

	private:
		//Offsets
		int mPosX, mPosY;

		//Current frame of animation
		int mFrame;

		//Type of particle
		LTexture *mTexture;
};

#endif