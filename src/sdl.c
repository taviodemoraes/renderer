#include "sdl.h"

// Init of SDL systems
bool init_sdl(sdl_t *sdl) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Could not init SDL systems! %s\n", SDL_GetError());
		return false;
	}

	sdl->window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!sdl->window) {
		SDL_Log("Could not create SDL window! %s\n", SDL_GetError());
		return false;
	}

	sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!sdl->renderer) {
		SDL_Log("Could not create SDL renderer! %s\n", SDL_GetError());
		return false;
	}

	return true;
}

// Exit & Destroy of SDL systems
void destroy_sdl(SDL_Renderer *renderer, SDL_Window *window) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
