#include <iostream>
#include "window.hpp"
#include "rng.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "color.hpp"
#include "world.hpp"
#include "camera.hpp"

// sdl2pp review.
//
// needs wrapper for CreateWindowAndRenderer
// needs GetHeight for Texture lock for consistency
// needs SetIntegerScaling for renderer
// No events.
// > -I /usr/include/SDL2 <
// > #include <SDL_...> <
// dont do this.

int main(int argc, char **argv)
try {
	constexpr int width = 200, height = 100;
	constexpr float aspect_ratio = float(width) / float(height);
	constexpr int scale = 4;
	constexpr int samples = 20;

	auto sdl = SDL2pp::SDL(SDL_INIT_VIDEO);
	auto [window, renderer, texture] =
		init_sdl(width, height, scale, "Ray Tracer");

	auto lookfrom = vec3(5, 3, 5);
	auto lookat   = vec3(0, 0, -1);
	auto up       = vec3(0, 1, 0);
	auto dist_to_focus = (lookfrom - lookat).length();
	auto aperture = 0.0;
	auto fov = 20;
	const auto cam = camera(
		lookfrom, lookat, up,
		fov, aspect_ratio, aperture, dist_to_focus);

	auto w = make_world();

	for (int x = 0; x < width; ++x) {
		renderer.SetTarget(texture);
		for (int y = 0; y < height; ++y) {
			auto c = vec3();
			for (int s = 0; s < samples; ++s) {
				auto u = (x + rng()) / float(width);
				auto v = 1.0 - (y + rng()) / float(height);
				auto r = cam(u, v);
				c += color(r, w);
			}
			c /= samples;
			c = sqrt(c);
			c *= 255.99;
			renderer.SetDrawColor(c.r(), c.g(), c.b());
			renderer.DrawPoint(x, y);
		}
		renderer.SetTarget();
		renderer.Copy(texture);
		renderer.Present();
	}

	// just idle until death
	SDL_Event event;
	auto should_quit = [](SDL_Event e) {
		if (e.type == SDL_QUIT) return true;
		if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_q)
			return true;
		return false;
	};
	do {
		renderer.Copy(texture);
		renderer.Present();
		SDL_PollEvent(&event);
		SDL_Delay(100);
	}
	while (! should_quit(event));
	return EXIT_SUCCESS;
} catch (SDL2pp::Exception const& e) {
	std::cerr << e.GetSDLFunction() << ": " << e.GetSDLError() << '\n';
	return EXIT_FAILURE;
} catch (std::exception const& e) {
	std::cerr << e.what() << '\n';
	return EXIT_FAILURE;
}
