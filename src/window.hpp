#include <SDL2pp/SDL2pp.hh>

struct sdl_tuple {
	SDL2pp::Window   w;
	SDL2pp::Renderer r;
	SDL2pp::Texture  t;
};
sdl_tuple init_sdl(int width, int height, int scale, const char* title);

