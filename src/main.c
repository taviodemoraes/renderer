#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "SDL.h"

#define WINDOW_WIDTH 	640
#define WINDOW_HEIGHT	320

bool should_quit = false;

// SDL Object
typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} sdl_t;

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

void draw_pixel(SDL_Renderer *renderer, int x, int y, uint32_t color) {
	SDL_SetRenderDrawColor(renderer, (color >> 24), (color >> 16), (color >> 8), (color >> 0));
	SDL_RenderDrawPoint(renderer, x, y);
}

/*
 * Bresenham's Line Algorithm
 * Draw lines by adjusting the line to the straightest possible line between two points
 * x0,y0: start point
 * x1,y1: end point
*/
void draw_line(SDL_Renderer *renderer, int x0, int y0, int x1, int y1) {
	// Calculate the deltas to determine the line primary direction
	const int dx = abs(x1 - x0);
	const int dy = abs(y1 - y0);

	// Calculate the step direction (in x-direction and y-direction)	
	const int sx = (x0 < x1) ? 1 : -1; // step x left or right
	const int sy = (y0 < y1) ? 1 : -1; // step y up or down

	// Ideal difference of line
	int err = dx - dy;

	while(1) {
		// Draw current pixel
		draw_pixel(renderer, x0, y0, 0xFF0000FF);
			
		// If the line is completed (x0 -> x1, y0 -> y1) exit the loop
		if (x0 == x1 && y0 == y1) break;	
		
		// Update error term (look ahead)
		int e2 = 2 * err;

		// Adjust x-coordinate
		if (e2 > -dy) {
			err -= dy; // adjust error term because the error is in x-coordinate
			x0 += sx; // move x0 in the x direction setup in sx (left or right)
		}

		// Adjust y-coordinate
		if (e2 < dx) {
			err += dx; // adjust error term because the error is in y-coordinate
			y0 += sy; // move y0 in the y direction setup in sy (up or down)
		}
	}	
}


void draw_triangle(SDL_Renderer *renderer) {
	// max_y = 320, max_x = 640
	// Calculate vertex for a trinagle in the mid of screen 
	const int center_x = WINDOW_WIDTH / 2;
	const int center_y = WINDOW_HEIGHT / 2;
	const int side_length = 320;
	const int height_length = (sqrt(3) / 2) * side_length;
	const int vertex1[2] = {center_x, center_y - height_length / 2};
	const int vertex2[2] = {center_x - side_length / 2, center_y + height_length / 2};
	const int vertex3[2] = {center_x + side_length / 2, center_y + height_length / 2};	
	draw_line(renderer, vertex1[0], vertex1[1], vertex2[0], vertex2[1]);
	draw_line(renderer, vertex2[0], vertex2[1], vertex3[0], vertex3[1]);
	draw_line(renderer, vertex3[0], vertex3[1], vertex1[0], vertex1[1]);
}

void handle_events(void) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			should_quit = true;
		}
	}
}

void destroy_sdl(SDL_Renderer *renderer, SDL_Window *window) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
