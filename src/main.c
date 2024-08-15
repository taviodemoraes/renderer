#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <SDL.h>

void draw_pixel(SDL_Renderer *renderer, int x, int y, uint32_t color) {
	SDL_SetRenderDrawColor(renderer, (color >> 24), (color >> 16), (color >> 8), (color >> 0));
	SDL_RenderDrawPoint(renderer, x, y);
}

/*
 * x1,y1: start point
 * x2,y2: end point
*/
void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
	const int dx = x2 - x1;
	const int dy = y2 - y1;
	// calculate slope with deltas 
	const int slope = dy/dx;
	// iterate through the length of line (x position)
	for (int x = x1; x < x2; x++) {
		// calculating the y of pixel with the slope
		int y = slope * (x - x1) + y1;
		draw_pixel(renderer, x, y, 0xFF0000FF);
	}	
}

int main(void) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	draw_line(renderer, 0, 0, 100, 100);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
