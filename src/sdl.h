#include <stdbool.h>

#include "SDL.h"

#define WINDOW_WIDTH	640
#define WINDOW_HEIGHT	320 

// SDL Object
typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} sdl_t;

// Init of SDL systems
bool init_sdl(sdl_t *sdl);
// Exit & Destroy of SDL systems
void destroy_sdl(SDL_Renderer *renderer, SDL_Window *window);
