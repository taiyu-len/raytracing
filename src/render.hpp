#ifndef RENDER_HPP
#define RENDER_HPP
#include "vec3.hpp"
#include "ray.hpp"
#include "hit_record.hpp"
#include "camera.hpp"
#include <vector>
#include <SDL2pp/SDL2pp.hh>

/**
 * @param[out] renderer the renderer to draw to
 * @param[out] tex The texture to use
 * @param h    The hitable object being rendered
 * @param cam  The camera used to generate rays
 * @param samples The number of samples per pixel to use
 */
void render(
	SDL2pp::Renderer &renderer,
	SDL2pp::Texture &tex,
	hitable const& h,
	camera const& cam,
	int samples);

#endif // RENDER_HPP
