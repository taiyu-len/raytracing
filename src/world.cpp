#include "world.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "rng.hpp"

void world::operator()(
	ray const* rs, float* ts, hit_record* hrs, size_t count) const
{
	for (auto &o : objects) {
		(*o)(rs, ts, hrs, count);
	}
}

static
void add_sphere(world& w, int i, int j)
{
	auto select_mat = rng();
	auto center = vec3{rng(i, i + 0.9), 0.2, rng(j, j+0.9)};
	if ((center - vec3{4, 0.2, 0}).length_sq() < 0.9*0.9)
		return;
	auto mat = std::unique_ptr<material>();
	auto sph = sphere();
	if (select_mat < 0.8) {
		auto clr = vec3{rng()*rng(), rng()*rng(), rng()*rng()};
		mat = std::make_unique<lambertian>(clr);
	} else if (select_mat < 0.95) {
		auto clr = vec3{rng(.5, 1), rng(.5, 1), rng(.5, 1)};
		mat = std::make_unique<metal>(clr);
	} else {
		mat = std::make_unique<dielectric>(rng(1.2, 1.5));
	}
	w.add_object<sphere>(center, 0.2, mat.get());
	w.materials.push_back(std::move(mat));
}

auto make_world(int size) -> world
{
	auto w = world();
	// bottom of the world
	w.materials.push_back(std::make_unique<lambertian>(vec3{.1, .5, .2}));
	// TODO find out why the normal has to be negative to be visible?
	w.add_object<plane>(vec3{0, -1, 0}, vec3{0, 0, 0}, w.materials[0].get());
	for (int i = -size; i < size; ++i) {
		for (int j = -size; j < size; ++j) {
			add_sphere(w, i, j);
		}
	}
	w.materials.push_back(std::make_unique<metal>(vec3{0.8, 0.8, 0.8}));
	w.add_object<sphere>(vec3{0, 1, 0}, 1, w.materials.back().get());
	return w;
}
