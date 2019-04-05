#include "render.hpp"
#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "rng.hpp"
#include <algorithm>
#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>

/* For each coordiante within the rectangle call f(x, y)
 * */
template<typename F>
void for_all_coor(SDL2pp::Rect rect, F f) {
	for (int dy = 0; dy < rect.h; ++dy) {
		for (int dx = 0; dx < rect.w; ++dx) {
			f(rect.x + dx, rect.y + dy);
		}
	}
}

/* For each coordinates within the rectangle 0,0, point call f(x, y) */
template<typename F>
void for_all_coor(SDL2pp::Point p, F f) {
	for_all_coor(SDL2pp::Rect(0, 0, p.x, p.y), f);
}


/**
 * @param rect same as in \ref render
 * @param size same as in \ref render
 * @param cam same as in \ref render
 * @param samples same as in \ref render
 * @param rays output parameter for the rays generated
 * @param indices stores the indices between rays of different coordinates.
 */
static
void initial_rays(
	const SDL2pp::Rect rect,
	const SDL2pp::Point size,
	camera const& cam,
	const int samples,
	std::vector<ray> &rays, std::vector<int> &indices)
{
	rays.reserve(rect.w * rect.h * samples + 1);
	indices.reserve(rect.w * rect.h + 1);
	for_all_coor(rect, [&](int x, int y) {
		for (int s = 0; s < samples; ++s) {
			auto u = (x + rng()) / float(size.x);
			auto v = 1.0 - (y + rng()) / float(size.y);
			rays.push_back(cam(u, v));
		}
		indices.push_back(rays.size());
	});
}

/**
 * @param rays set of input rays
 * @param hrs  output hit records for each ray
 * @param h    hitable object to test against
 */
static
void calculate_hit_records(
	std::vector<ray> const& rays,
	std::vector<hit_record> &hrs,
	hitable const& h)
{
	const auto inf = std::numeric_limits<float>::infinity();
	auto ts = std::vector<float>(rays.size(), inf);
	hrs.clear();
	hrs.resize(rays.size());

	// calculate hit records for h
	h(rays.data(), ts.data(), hrs.data(), rays.size());
}

/** Filters out the rays that have been completed, black colors or hit
 * background.
 * @param[in] rect the area we are drawing to
 * @param[in] hrs hit records for each ray
 * @param[in,out] colors the current color of each ray
 * @param[in,out] rays to be filtered
 * @param[in,out] idxs to determine coordinates of rays
 * @param[in,out] final_colors to add finished colors to the coordinate
 */
static
void filter_finished_rays(
	SDL2pp::Rect rect,
	std::vector<hit_record> const& hrs,
	std::vector<vec3> & colors,
	std::vector<ray> &rays,
	std::vector<int> &idxs,
	std::vector<vec3> &final_colors
) {
	auto index = 0; // the current ray we are checking
	auto coor = 0;  // the current coordinate of the ray
	auto next_index = 0; // the next index we move active rays into.
	auto removed = 0; // how many have been removed so far.

	for_all_coor(rect.GetSize(), [&](int x, int y) {
		while (index < idxs[coor]) {
			const bool no_hits = hrs[index].mat == nullptr;
			const bool too_dark = colors[index].length_sq() < 0.001;
			if (no_hits) {
				final_colors[coor] += colors[index];
			}
			// if the current one is valid move it to next_index
			if (!no_hits && !too_dark) {
				colors[next_index] = colors[index];
				rays[next_index] = rays[index];
				++next_index;
			} else {
				++removed;
			}
			++index;
		}
		idxs[coor] -= removed;
		++coor;
	});
	rays.resize(rays.size() - removed);
	colors.resize(colors.size() - removed);
}


/**
 * @param[in,out] surface the surface being drawn too.
 * @param rect The section of the image being rendered
 * @param size The size of the total image
 * @param h    The hitable object being rendered
 * @param cam  The camera used to generate rays
 * @param samples The number of samples per pixel to use
 */
static
void render_to_texture(
	SDL2pp::Texture &texture,
	SDL2pp::Rect rect,
	SDL2pp::Point size,
	hitable const& h,
	camera const& cam,
	const int samples)
{
	auto rays = std::vector<ray>();
	auto idxs = std::vector<int>();
	auto hrs  = std::vector<hit_record>();

	auto final_colors = std::vector<vec3>(rect.w * rect.h);

	initial_rays(rect, size, cam, samples, rays, idxs);
	calculate_hit_records(rays, hrs, h);
	auto colors = std::vector<vec3>(hrs.size(), vec3{1, 1, 1});
	color(hrs, rays, colors);

	// calculate colors for rays, and filter out finished rays
	filter_finished_rays(rect, hrs, colors, rays, idxs, final_colors);

	// calculate rays and colors
	for (int iter = 0; iter < 10 && rays.size() > 0; ++iter) {
		calculate_hit_records(rays, hrs, h);
		color(hrs, rays, colors);
		filter_finished_rays(rect, hrs, colors, rays, idxs, final_colors);
	}
	// final colors
	

	// draw to surface
	auto format = SDL_AllocFormat(texture.GetFormat());
	auto texture_lock = texture.Lock(rect);
	auto pixels = static_cast<Uint32*>(texture_lock.GetPixels());
	auto pitch  = texture_lock.GetPitch();

	auto coor = 0;  // the current coordinate
	for_all_coor(rect.GetSize(), [&](int x, int y) {
		auto c = final_colors[coor];
		c *= 255.9;
		c /= samples;
		auto pixel = SDL_MapRGB(format, c.r(), c.g(), c.b());
		pixels[x + y*(pitch/sizeof(Uint32))] = pixel;
		++coor;
	});
	SDL_FreeFormat(format);
}

void render(
	SDL2pp::Renderer &renderer,
	SDL2pp::Texture &tex,
	hitable const& h,
	camera const& cam,
	int samples)
{
	const auto step = 32;
	const auto size = tex.GetSize();
	auto rect = SDL2pp::Rect(0, 0, step, step);
	for (; rect.x < size.x; rect.x += step) {
		if (rect.x + step > size.x) {
			rect.w = size.x - rect.x;
		}
		rect.h = step;
		for (rect.y = 0; rect.y < size.y; rect.y += step) {
			if (rect.y + step > size.y) {
				rect.h = size.y - rect.y;
			}
			render_to_texture(tex, rect, size, h, cam, samples);
			renderer.Copy(tex, rect, rect);
			renderer.Present();
		}
	}

}
