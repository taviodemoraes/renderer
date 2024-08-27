#include "triangle.h"
#include "graphics.h"
#include "vector.h"
#include <math.h>

void draw_triangle(SDL_Renderer *renderer, vec2_t a, vec2_t b, vec2_t c) {
	draw_line(renderer, a.x, a.y, b.x, b.y);
	draw_line(renderer, b.x, b.y, c.x, c.y);
	draw_line(renderer, c.x, c.y, a.x, a.y);
}

float get_triangle_area(vec2_t a, vec2_t b, vec2_t c) {
	vec2_t ab = vec2_sub(a, b);
	vec2_t ac = vec2_sub(a, c);
	return abs(vec2_cross_product(ab, ac)) / 2;
}

vec3_t barycentric_weights(vec2_t a, vec2_t b, vec2_t c, vec2_t p) {
	float triangle_area = get_triangle_area(a, b, c);
	// Sub triangle PBC / triangle_area
	float alpha = get_triangle_area(p, b, c) / triangle_area;
	// Sub triangle APC / triangle_area
	float beta = get_triangle_area(a, p, c) / triangle_area;
	// alpha + beta + gamma = 1
	float gamma = 1 - alpha - beta;
	vec3_t weights = {alpha, beta, gamma};
	return weights;
}

void draw_filled_triangle(SDL_Renderer *renderer, vec2_t a, vec2_t b, vec2_t c) {
	// Get the bounding box of the triangle
	int max_x = fmax(a.x, fmax(b.x, c.x));
	int min_x = fmin(a.x, fmin(b.x, c.x));
	int max_y = fmax(a.y, fmax(b.y, c.y));
	int min_y = fmin(a.y, fmin(b.y, c.y));

	float triangle_area = get_triangle_area(a, b, c);
	float area_sum = 0;
	
	// Iterate through all the pixels of bounding box
	for (int x = min_x; x <= max_x; x++) {
		for (int y = min_y; y <= max_y; y++) {
			vec2_t p = {.x = x, .y = y};
			
			// Get the sum of area of the 3 sub triangles
			area_sum = get_triangle_area(a, b, p) + get_triangle_area(a, c, p) + get_triangle_area(b, c, p);
			 
			vec3_t weights = barycentric_weights(a, b, c, p);

			// Barycentric coordinates (how close the point is from each vertex)
			float alpha = weights.y;
			float beta  = weights.x;
			float gamma = weights.z;
		
			// Get the RGB color for point based in the coordinates
			int r = (alpha) * 0xFF + (beta) * 0x00 + (gamma) * 0x00;
			int g = (alpha) * 0x00 + (beta) * 0xFF + (gamma) * 0x00;
			int b = (alpha) * 0x00 + (beta) * 0x00 + (gamma) * 0xFF;
	
			uint32_t interpolate_color = (r << 24) + (g << 16) + (b << 8) + (0xFF);
			
			/* If the sum of area of sub triangles (that point is one vertex)
		   	   is equal to the triangle area, the point is inside of triangle
			*/
			if (triangle_area == area_sum) {
				// inside triangle
				draw_pixel(renderer, p.x, p.y, interpolate_color);
			}
		}
	}
}
