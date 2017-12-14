#include <stdio.h>
#include <SDL2/SDL.h>

//Screen Dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Window functions
int game_init();

//Closes SDL
void game_close();

//Loads individual images
SDL_Surface* loadSurface(char* path);

//Loads media
int loadMedia();

//The window that will be rendered to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The current surface on the screen
SDL_Surface* gCurrentSurface = NULL;


int game_init() {
	int success = 1;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL! SDL Error: %s\n", SDL_GetError());
		success = 0;
	} else {
		//Create window
		gWindow = SDL_CreateWindow("Optimized Surface", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Could not create window! SDL Error: %s\n", SDL_GetError());
			success = 0;
		} else {
			//Create window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}


SDL_Surface* loadSurface(char* path) {

	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at the specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if(loadSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	} else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if(optimizedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

	}

	return optimizedSurface;
}


int loadMedia() {
	//Success flag
	int success = 1;

	gCurrentSurface = loadSurface("Images/stretch.bmp");
	if(gCurrentSurface == NULL) {
		printf("Could not current surface!\n");
		success = 0;
	}

	return success;
}


void game_close() {

	//Deallocating current surface
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	//Destroy current window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit all SDL subsystems
	SDL_Quit();

}


int main(int argc, char* argv[]) {

	printf("Everything is working so far!\n");

	if(game_init() == 0) {
		printf("Could not initialize!\n");
	} else {
		if(loadMedia() == 0) {
			printf("Could not load media!\n");
		} else {

			//Quit handler
			int quit = 0;

			//Event handler
			SDL_Event e;

			while(quit == 0) {
				while(SDL_PollEvent(&e) != 0) {
					if(e.type == SDL_QUIT) {
						quit = 1;
					}
				}

				//Apply the image stretched
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);

				// SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	return 0;
}