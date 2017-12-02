#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
	
	printf("Hello world!\n");

	//SDL window
	SDL_Window* window = NULL;

	//SDL surface
	SDL_Surface* screenSurface = NULL;

	//Init SDL 
	if ( SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initalize! SDL_Error: %s\n", SDL_GetError());
	} else {
		//Create window
		window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED,
		 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		} else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Wait two seconds
			SDL_Delay(2000);
		}
	}

	return 0;
}
