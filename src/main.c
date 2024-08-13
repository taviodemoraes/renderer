#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <SDL.h>

void draw_pixel(SDL_Renderer *renderer, int x, int y, uint32_t color) {
	SDL_SetRenderDrawColor(renderer, (color >> 24), (color >> 16), (color >> 8), (color >> 0));
	SDL_RenderDrawPoint(renderer, x, y);
}

int main(void) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	draw_pixel(renderer, 400, 300, 0xFF0000FF);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
