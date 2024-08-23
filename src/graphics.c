#include "graphics.h"
#include "vector.h"
#include <math.h>

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
	// Calculate the deltas to determine the line primary directin
	const int dx = abs(x1 - x0);
	const int dy = abs(y1 - y0);
	
	// Calculate the step direction (in x-direction and y-direction)
	const int sx = (x0 < x1) ? 1 : -1; // step x left or right
	const int sy = (y0 < y1) ? 1 : -1; // step y up or down

	// Ideal difference of line
	int err = dx - dy;
	
	while (1) {
		// Draw current pixel
		draw_pixel(renderer, x0, y0, 0xFF0000FF);
		
		// If the line is completed (x0 -> x1, y0 -> y1) exit the loop
		if (x0 == x1 && y0 == y1) break;
	
		// Update error term (look ahead)
		int e2 = 2 *err;


		// Adjust x-coordinate
		if (e2 > -dy) {
			err -= dy; // adjust error term because the error is in x-coordinate
			x0 += sx; // move x0 in the x-direction setup in sx (left or right)
		}

		// Adjust y-coordinate
		if (e2 < dx) {
			err += dx; // adjust error term because the error is in y-coordinate	
			y0 += sy; // move y0 in the y-direction setup in sy (up or down)
		}
	}
}

void draw_triangle(SDL_Renderer *renderer) {
	// Calculate vertex for a triangle in the mid of screen
	const int center_x = 640 / 2;
	const int center_y = 320 / 2;
	const int side_length = 320;
	const int height_length = (sqrt(3) / 2)	* side_length;
	vec2_t v1 = {.x = center_x, .y = center_y - height_length / 2};
	vec2_t v2 = {.x = center_x - side_length / 2, .y = center_y + height_length / 2};
	vec2_t v3 = {.x = center_x + side_length / 2, center_y + height_length / 2};
	draw_line(renderer, v1.x, v1.y, v2.x, v2.y);
	draw_line(renderer, v2.x, v2.y, v3.x, v3.y);
	draw_line(renderer, v3.x, v3.y, v1.x, v1.y);	
}

int get_triangle_area(vec2_t a, vec2_t b, vec2_t c) {
	vec2_t ab = vec2_sub(a, b);
	vec2_t ac = vec2_sub(a, c);
	return abs(vec2_cross_product(ab, ac)) / 2;
}

void draw_filled_triangle(SDL_Renderer *renderer) {
	// Calculate vertex for a triangle in the mid of screen
	const int center_x = 640 / 2;
	const int center_y = 320 / 2;
	const int side_length = 320;
	const int height_length = (sqrt(3) / 2)	* side_length;
	vec2_t v1 = {.x = center_x, .y = center_y - height_length / 2};
	vec2_t v2 = {.x = center_x - side_length / 2, .y = center_y + height_length / 2};
	vec2_t v3 = {.x = center_x + side_length / 2, center_y + height_length / 2};

	// Get the bounding box of the triangle
	int max_x = fmax(v1.x, fmax(v2.x, v3.x));
	int min_x = fmin(v1.x, fmin(v2.x, v3.x));
	int max_y = fmax(v1.y, fmax(v2.y, v3.y));
	int min_y = fmin(v1.y, fmin(v2.y, v3.y));		

	int triangle_area = get_triangle_area(v1, v2, v3);
	int area_sum = 0;

	// Iterate through all the pixels of bouding box
	for (int x = min_x; x <= max_x; x++) {
		for (int y = min_y; y <= max_y; y++) {
			vec2_t p = {.x = x, .y = y};
			area_sum = get_triangle_area(v1, v2, p) + get_triangle_area(v1, v3, p) + get_triangle_area(v2, v3, p);
						
			/* If the sum of area of sub triangles (that point is one of vertex) 
			   is equal to the triangle area, the point is inside of triangle
			*/
			if (triangle_area == area_sum) {
				// inside triangle
				draw_pixel(renderer, x, y, 0xFFFF00FF);
			}
		}
	}	
}
