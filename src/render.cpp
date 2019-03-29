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

void render_row(
	std::vector<Uint32>& pixels,
	int y, int max_y,
	int samples, world const& w, camera const& cam,
	SDL_PixelFormat const* fmt)
{
	for (int i = 0; i < pixels.size(); ++i) {
		// sample colors
		auto c = vec3();
		for (int s = 0; s < samples; ++s) {
			auto u = (i + rng()) / float(pixels.size());
			auto v = 1.0 - (y + rng()) / float(max_y);
			auto r = cam(u, v);
			c += color(r, w);
		}
		c /= samples;
		c = sqrt(c);
		c *= 255.99;
		auto pixel = SDL_MapRGB(fmt, c.r(), c.g(), c.b());
		pixels[i] = pixel;
	}
}

void render(
	SDL2pp::Renderer& renderer, SDL2pp::Texture& texture,
	world const& w, camera const& cam, const int samples)
{
	const auto size = texture.GetSize();
	std::cout << "texture size: " << size << '\n';
	// Pixel format
	auto fmt = SDL_AllocFormat(texture.GetFormat());

	// draw rows
	std::mutex render_mtx;
	auto thread_count = std::thread::hardware_concurrency();
	auto chunk_count = thread_count * 8;
	auto chunk_size  = (size.y / chunk_count) + 1;
	auto chunk = std::atomic<int>(0);

	auto draw_row = [&](std::vector<Uint32>& pixels, int row)
	{
		render_row(pixels, row, size.y, samples, w, cam, fmt);
		auto section = SDL2pp::Rect(0, row, size.x, 1);
		auto lg = std::lock_guard<std::mutex>(render_mtx);
		{
			auto tex = texture.Lock(section);
			auto data = static_cast<Uint32*>(tex.GetPixels());
			std::copy(pixels.begin(), pixels.end(), data);
		}
		renderer.Copy(texture);
		renderer.Present();
	};
	auto job = [&]
	{
		auto pixels = std::vector<Uint32>(size.x);
		for (
			auto my_chunk = chunk++;
			my_chunk < chunk_count;
			my_chunk = chunk++) {
			auto row = my_chunk * chunk_size;
			auto end = std::min((my_chunk + 1) * chunk_size, (unsigned)size.y);
			printf("drawing from %d to %d\n", row, end);
			for (; row < end; ++row) {
				draw_row(pixels, row);
			}
		}
	};
	auto threads = std::vector<std::thread>();
	for (auto i = 0; i < thread_count; ++i)
		threads.emplace_back(job);
	for (auto& t : threads)
		t.join();

	SDL_FreeFormat(fmt);
}
