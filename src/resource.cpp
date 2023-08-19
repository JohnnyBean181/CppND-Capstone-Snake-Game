#include "resource.h"

LTexture gRedTexture;
LTexture gGreenTexture;
LTexture gBlueTexture;
LTexture gShimmerTexture;

// load images to create particles
bool LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Load red texture
	if( !gRedTexture.loadFromFile( "red.bmp" ) )
	{
		printf( "Failed to load red texture!\n" );
		success = false;
	}

	//Load green texture
	if( !gGreenTexture.loadFromFile( "green.bmp" ) )
	{
		printf( "Failed to load green texture!\n" );
		success = false;
	}

	//Load blue texture
	if( !gBlueTexture.loadFromFile( "blue.bmp" ) )
	{
		printf( "Failed to load blue texture!\n" );
		success = false;
	}

	//Load shimmer texture
	if( !gShimmerTexture.loadFromFile( "shimmer.bmp" ) )
	{
		printf( "Failed to load shimmer texture!\n" );
		success = false;
	}
	
	//Set texture transparency
	gRedTexture.setAlpha( 192 );
	gGreenTexture.setAlpha( 192 );
	gBlueTexture.setAlpha( 192 );
	gShimmerTexture.setAlpha( 192 );

	return success;
}

void UnLoadMedia() {
    //Free loaded images
	gRedTexture.free();
	gGreenTexture.free();
	gBlueTexture.free();
	gShimmerTexture.free();
}