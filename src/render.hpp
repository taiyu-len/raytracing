#ifndef RENDER_HPP
#define RENDER_HPP
#include "vec3.hpp"
#include "world.hpp"
#include "camera.hpp"
#include <SDL2pp/SDL2pp.hh>

void render(
	SDL2pp::Renderer& renderer, SDL2pp::Texture& texture,
	world const& w, camera const& cam, const int samples);

#endif // RENDER_HPP
