#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#include <string>
#include <iostream>

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( SDL_Renderer *sdl_renderer, std::string path);

		//Creates image from font string
		bool loadFromRenderedText( TTF_Font* gFont, SDL_Renderer *sdl_renderer, std::string textureText, SDL_Color textColor );

		//Deallocates texture
		void free();

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );
		
		//Renders texture at given point
		void render( SDL_Renderer *sdl_renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();

		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};


#endif