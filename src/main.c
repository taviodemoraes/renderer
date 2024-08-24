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

	point_t v1 = {.x = 320, .y = 102};
	point_t v2 = {.x = 270, .y = 188};
	point_t v3 = {.x = 370, .y = 188};
	
	while (!should_quit) {
		handle_events();
		// Rendering
		draw_filled_triangle(sdl.renderer, v1, v2, v3);
		SDL_RenderPresent(sdl.renderer);
	}
	
	destroy_sdl(sdl.renderer, sdl.window);
	exit(EXIT_SUCCESS);
}
