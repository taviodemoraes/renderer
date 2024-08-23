#include "vector.h"

vec2_t vec2_sub(vec2_t a, vec2_t b) {
	vec2_t result = {
		.x = a.x - b.x,
		.y = a.y - b.y
	};	
	return result;
}

int vec2_cross_product(vec2_t a, vec2_t b) {
	return (a.x * b.y) - (a.y * b.x);
}
