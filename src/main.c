#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include <SDL.h>

#define WINDOW_WIDTH 	640
#define WINDOW_HEIGHT	320

void draw_pixel(SDL_Renderer *renderer, int x, int y, uint32_t color) {
	SDL_SetRenderDrawColor(renderer, (color >> 24), (color >> 16), (color >> 8), (color >> 0));
	SDL_RenderDrawPoint(renderer, x, y);
}

/*
 * Bresenham's Line Algorithm
 * x0,y0: start point
 * x1,y1: end point
*/
void draw_line(SDL_Renderer *renderer, int x0, int y0, int x1, int y1) {
	// Calculate the deltas to determine the line primary direction
	const int dx = abs(x1 - x0);
	const int dy = abs(y1 - y0);

	// Calculate the step direction (in x-direction and y-direction)	
	const int sx = (x0 < x1) ? 1 : -1; // step x left or right
	const int sy = (y0 < y1) ? 1 : -1; // step y left or right

	// Start state for difference between dx and dy
	int err = dx - dy;

	while(1) {
		// Draw current pixel
		draw_pixel(renderer, x0, y0, 0xFF0000FF);
			
		// If the line is completed (x0 -> x1, y0 -> y1) exit the loop
		if (x0 == x1 && y0 == y1) break;	
		
		// Update error term (look ahead)
		int e2 = 2 * err;

		// Update x-coordinate
		if (e2 > -dy) {
			err -= dy;
			x0 += sx; // move x0 in the x direction setup in sx (left or right)
		}

		// Update y-coordinate
		if (e2 < dx) {
			err += dx;
			y0 += sy; // move y0 in the y direction setup in sy (left or right)
		}
	}	
}

int main(void) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	draw_line(renderer, 0, 0, 10, 10);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
