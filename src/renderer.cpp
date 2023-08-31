#include "renderer.h"


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //Initialize SDL_ttf
  if( TTF_Init() == -1 )
  {
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
  }

  // load image to generate particles.
  LoadImage();
}

bool Renderer::LoadImage() {

	//Loading success flag
	bool success = true;

  //Load red texture
	if( !gRedTexture.loadFromFile( sdl_renderer, "../bmp/red.bmp" ) )
	{
		printf( "Failed to load red texture!\n" );
		success = false;
	}

	//Load green texture
	if( !gGreenTexture.loadFromFile( sdl_renderer, "../bmp/green.bmp" ) )
	{
		printf( "Failed to load green texture!\n" );
		success = false;
	}

	//Load blue texture
	if( !gBlueTexture.loadFromFile( sdl_renderer, "../bmp/blue.bmp" ) )
	{
		printf( "Failed to load blue texture!\n" );
		success = false;
	}

	//Load shimmer texture
	if( !gShimmerTexture.loadFromFile( sdl_renderer, "../bmp/shimmer.bmp" ) )
	{
		printf( "Failed to load shimmer texture!\n" );
		success = false;
	}
	
	//Set texture transparency
	gRedTexture.setAlpha( 192 );
	gGreenTexture.setAlpha( 192 );
	gBlueTexture.setAlpha( 192 );
	gShimmerTexture.setAlpha( 192 );

	//Open the font
	gFont = TTF_OpenFont( "../font/lazy.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text 1P
		SDL_Color textColor = { 0xff, 0xff, 0xff };
		if( !gTextTexture_1p.loadFromRenderedText( gFont, sdl_renderer, "Start Game - 1P", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}

		//Render text PvP
		if( !gTextTexture_2p.loadFromRenderedText( gFont, sdl_renderer, "Start Game - PvP", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}

    //Render text PvC
		if( !gTextTexture_pvc.loadFromRenderedText( gFont, sdl_renderer, "Start Game - PvC", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}

		//Render text Exit
		if( !gTextTexture_exit.loadFromRenderedText( gFont, sdl_renderer, "Exit", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}

  //Create the mutex
  gBufferLock = SDL_CreateMutex();

  //Create conditions
  gCanProduce = SDL_CreateCond();
  gCanEat = SDL_CreateCond();
  gCanThrow = SDL_CreateCond();

	return success;
}

Renderer::~Renderer() {
  // release loaded image
  UnloadImage();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

  //Destroy the mutex
  SDL_DestroyMutex( gBufferLock );
  gBufferLock = NULL;

  //Destroy conditions
  SDL_DestroyCond (gCanProduce );
  SDL_DestroyCond (gCanEat );
  SDL_DestroyCond (gCanThrow );
  gCanProduce = NULL;
  gCanEat = NULL;
  gCanThrow = NULL;

  //Destroy window
  SDL_DestroyRenderer( sdl_renderer );
  SDL_DestroyWindow(sdl_window);
  sdl_window = NULL;
  sdl_renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Renderer::UnloadImage() {
  //Release loaded images
	gRedTexture.free();
	gGreenTexture.free();
	gBlueTexture.free();
	gShimmerTexture.free();

  //Free loaded images
	gTextTexture_1p.free();
}

void Renderer::DrawText(int id, int flag) {
  SDL_Color textColor;
  if (flag) {
    textColor = { 0x00, 0xff, 0xff };
  } else {
    textColor = { 0xff, 0xff, 0xff };
  }
  switch (id){
    case 0: 
      gTextTexture_1p.loadFromRenderedText( gFont, sdl_renderer, "Start Game - 1P", textColor );
      break;
    case 1: 
      gTextTexture_2p.loadFromRenderedText( gFont, sdl_renderer, "Start Game - PvP", textColor );
      break;
    case 2: 
      gTextTexture_pvc.loadFromRenderedText( gFont, sdl_renderer, "Start Game - PvC", textColor );
      break;
    case 3: 
      gTextTexture_exit.loadFromRenderedText( gFont, sdl_renderer, "Exit", textColor );
      break;
  }
}

void Renderer::Render(Snake* snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's particles
  if (snake->GetSolo()) {
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        snake->particles[ i ]->render(sdl_renderer);
    }
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(Snake* snake, Food* food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  if (food->IsPoisonous()) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xDD, 0x00, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  }
  block.x = food->GetPosition()->x * block.w;
  block.y = food->GetPosition()->y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's particles
  if (snake->GetSolo()) {
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        snake->particles[ i ]->render(sdl_renderer);
    }
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(Snake* snake1, Snake* snake2, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake1->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  
  // Render 2nd snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake2->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake1->head_x) * block.w;
  block.y = static_cast<int>(snake1->head_y) * block.h;
  if (snake1->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  
  // Render 2nd snake's head
  block.x = static_cast<int>(snake2->head_x) * block.w;
  block.y = static_cast<int>(snake2->head_y) * block.h;
  if (snake2->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xCC, 0x2A, 0x00, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderMainMenu(int &menu_selected, int &menu_last_selected) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  for(int i=0; i<4; i++) {
    if (menu_last_selected == i) {
      DrawText(i, 0);
      menu_last_selected = -1;
    }
    if (menu_selected == i) {
      DrawText(i, 1);
    } 
  }

  // Render current frame
  gTextTexture_1p.render(sdl_renderer, 200, 180);
  gTextTexture_2p.render(sdl_renderer, 200, 230);
  gTextTexture_pvc.render(sdl_renderer, 200, 280);
  gTextTexture_exit.render(sdl_renderer, 200, 330);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
