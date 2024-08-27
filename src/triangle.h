#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "SDL.h"
#include "graphics.h"
#include "vector.h"

void draw_triangle(SDL_Renderer *renderer, vec2_t a, vec2_t b, vec2_t c);

void draw_filled_triangle(SDL_Renderer *renderer, vec2_t a, vec2_t b, vec2_t c);

#endif
