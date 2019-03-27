#include "window.hpp"
#include <stdexcept>
#include <string>

sdl_tuple init_sdl(int width, int height, int scale, const char* title)
{
	using namespace SDL2pp;
	auto window = Window(
		"Ray Tracer",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width*scale, height*scale, 0);

	auto renderer = Renderer(window, -1, 0);
	renderer.SetScale(scale, scale);

	auto texture  = Texture(
		renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET,
		width, height);
	return {
		std::move(window),
		std::move(renderer),
		std::move(texture)
	};
}
