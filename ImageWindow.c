#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimensions
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 480;

//Starts up SDL and creates window
int game_init();

//Loads media
int loadMedia();

//Frees media and shuts down SDL
void game_close();

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;

int game_init() {
	//Initialization flag
	int success = 1;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = 0;
	} else {
		//Create window
		gWindow = SDL_CreateWindow("SDL Image Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = 0;
		} else {
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

int loadMedia() {
	//Loading success flag
	int success = 1;

	gHelloWorld = SDL_LoadBMP("Images/hello_world.bmp");
	if(gHelloWorld == NULL) {
		printf("Unable to load image %s! SDL_Error: %s\n", "Images/hello_world.bmp", SDL_GetError());
		success = 0;
	}
	return success;
}

void game_close() {
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char *argv[]) {

	printf("Everything is working!\n");

	//Start up SDL and create window
	if(game_init() == 0) {
		printf("Failed to initialize\n");
	} else {
		//Load media
		if(loadMedia() == 0) {
			printf("Failed to load media!\n");
		} else {

			//Main loop flag
			int quit = 0;

			//Event handler
			SDL_Event e;

			//While application is running
			while(quit == 0) {
				//Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = 1;
					}
				}
				//Apply the image
				SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	//Free resources and close SDL
	game_close();

	printf("The end has been reached!\n");

	return 0;
}
