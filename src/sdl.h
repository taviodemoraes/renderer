#ifndef SDL_H
#define SDL_H

#include <stdbool.h>

#include "SDL.h"

#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	320 

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} sdl_t;

bool init_sdl(sdl_t *sdl);

void destroy_sdl(SDL_Renderer *renderer, SDL_Window *window);

#endif
