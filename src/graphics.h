#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"

void draw_pixel(SDL_Renderer *renderer, int x, int y, uint32_t color);

void draw_line(SDL_Renderer *renderer, int x0, int y0, int x1, int y1);

void draw_triangle(SDL_Renderer *renderer);

void draw_filled_triangle(SDL_Renderer *renderer);

#endif
