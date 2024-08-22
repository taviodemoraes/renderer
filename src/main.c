#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "sdl.h"
#include "graphics.h"

bool should_quit = false;

void handle_events(void) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			should_quit = true;
		}
	}
}

int main(int argc, char **argv) {
	sdl_t sdl = {0};
	if (!init_sdl(&sdl)) exit(EXIT_FAILURE);

	while (!should_quit) {
		handle_events();
		// Rendering
		draw_triangle(sdl.renderer);
		SDL_RenderPresent(sdl.renderer);
	}
	
	destroy_sdl(sdl.renderer, sdl.window);
	exit(EXIT_SUCCESS);
}
