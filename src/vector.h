#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	int x;
	int y;
} vec2_t;

vec2_t vec2_sub(vec2_t a, vec2_t b);
int vec2_cross_product(vec2_t a, vec2_t b);

#endif 
