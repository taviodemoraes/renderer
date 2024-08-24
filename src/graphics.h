#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"

typedef struct {
	int x;	
	int y;
} point_t;

void draw_pixel(SDL_Renderer *renderer, int x, int y, uint32_t color);

void draw_line(SDL_Renderer *renderer, int x0, int y0, int x1, int y1);

void draw_triangle(SDL_Renderer *renderer, point_t v1, point_t v2, point_t v3);

void draw_filled_triangle(SDL_Renderer *renderer, point_t v1, point_t v2, point_t v3);

#endif
