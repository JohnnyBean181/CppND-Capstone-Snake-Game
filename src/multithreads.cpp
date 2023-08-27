#include "multithreads.h"
#include "game_adv_food.h"

int Producer( void *data )
{
	// printf( "\nProducer started...\n" );

	//Seed thread random
	// srand( SDL_GetTicks() );
    GameAdvFood* game = (GameAdvFood *)data;

    //Produce
    while(game->running) {
        //Wait
		SDL_Delay( 100 );

        //Produce
        Produce((GameAdvFood *)data);
    }

	// printf( "Producer finished!\n" );

    return 0;
}


int Consumer( void *data )
{
	// printf( "Consumer started...\n" );

	//Seed thread random
	// srand( SDL_GetTicks() );
    GameAdvFood* game = (GameAdvFood *)data;

	// SDL_Delay( 200 );

    while(game->running) {
        //Wait
		SDL_Delay( 100 );

        //Consume
        Consume((GameAdvFood *)data);
    }
	
	// printf( "Consumer finished!\n" );

	return 0;
}

void Produce(GameAdvFood* game)
{
	//Lock
	SDL_LockMutex( gBufferLock );
	
	//If the food is available
	if( game->IsFoodAvailable() )
	{
		//Wait for buffer to be cleared
		//printf( "\nProducer encountered full buffer, waiting for consumer to empty buffer...\n" );
		SDL_CondWait( gCanProduce, gBufferLock );
	}

	//Fill and show buffer
	game->MakeFood();
	//printf( "Produced %d\n", gData );
    // printf( "Food placed! \n" );
	
	//Unlock
	SDL_UnlockMutex( gBufferLock );
	
	//Signal consumer
	SDL_CondSignal( gCanEat );
	SDL_CondSignal( gCanThrow );
}

void Consume(GameAdvFood* game)
{
	//Lock
	SDL_LockMutex( gBufferLock );
	
	//If the buffer is empty
	if( !game->IsFoodAvailable() )
	{
		//Wait for buffer to be filled

		//printf( "\nConsumer encountered empty buffer, waiting for producer to fill buffer...\n" );
		SDL_CondWait( gCanThrow, gBufferLock );
	}

	//Show and empty buffer
    Uint32 current_timestamp = SDL_GetTicks();
    bool decayed = game->IsFoodDecayed(current_timestamp);
    if (decayed) {
        game->CleanFood();

        //Signal producer
	    SDL_CondSignal( gCanProduce );
    }

	//printf( "\nConsumed \n" );
	
	//Unlock
	SDL_UnlockMutex( gBufferLock );
}
