#include <iostream>
#include "window.hpp"
#include "rng.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "color.hpp"
#include "world.hpp"
#include "camera.hpp"
#include "render.hpp"
#include <chrono>

int main(int argc, char **argv)
try {
	constexpr int width = 800, height = 400;
	constexpr float aspect_ratio = float(width) / float(height);
	constexpr int scale   = 2;
	constexpr int samples = 100;

	auto sdl = SDL2pp::SDL(SDL_INIT_VIDEO);
	auto [window, renderer, texture] = init_sdl(
		width, height, scale, "Ray Tracer");

	auto lookfrom = vec3{10, 1, 5};
	auto lookat   = vec3{0, 0, -1};
	auto up       = vec3{0, 1, 0};
	auto dist_to_focus = (lookfrom - lookat).length();
	auto aperture = 0.0;
	auto fov = 20;
	const auto cam = camera(
		lookfrom, lookat, up,
		fov, aspect_ratio, aperture, dist_to_focus);

	auto w = make_world(5);
	auto start_time = std::chrono::high_resolution_clock::now();
	render(renderer, texture, w, cam, samples);
	auto end_time = std::chrono::high_resolution_clock::now();
	auto diff_time = std::chrono::duration<double>(end_time-start_time);
	std::cout << "Time to render " << diff_time.count() << '\n';

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
