#include "world.hpp"
#include "rng.hpp"
auto world::hit(ray r, float tmin, float tmax) const
	-> std::optional<hit_record> {
	auto best = hit_test(spheres.begin(), spheres.end(), r, tmin, tmax);
	// best = hit_test(tris.begin(), tris.end(), r, tmin, tmax, best);
	return best;
}

void add_sphere(world& w, int i, int j)
{
	auto select_mat = rng();
	auto center = vec3(rng(i, i + 0.9), 0.2, rng(j, j+0.9));
	if ((center - vec3(4,0.2,0)).length_sq() < 0.9*0.9)
		return;
	auto mat = std::unique_ptr<material>();
	auto sph = sphere();
	if (select_mat < 0.8) {
		auto clr = vec3(rng()*rng(), rng()*rng(), rng()*rng());
		mat = std::make_unique<lambertian>(clr);
		sph = sphere(center, 0.2, mat.get());
	} else if (select_mat < 0.95) {
		auto clr = vec3(rng(.5, 1), rng(.5, 1), rng(.5, 1));
		mat = std::make_unique<metal>(clr);
		sph = sphere(center, 0.2, mat.get());
	} else {
		mat = std::make_unique<dielectric>(rng(1.2, 1.5));
		sph = sphere(center, 0.2, mat.get());
	}
	w.materials.push_back(std::move(mat));
	w.spheres.push_back(sph);
}

auto make_world(int size) -> world
{
	auto w = world();
	// bottom of the world
	w.materials.emplace_back(new lambertian(vec3(1, 2, 5) / 10));
	w.spheres.emplace_back(vec3(0, -1000, 0), 1000, w.materials[0].get());
	for (int i = -5; i < 5; ++i) {
		for (int j = -5; j < 5; ++j) {
			add_sphere(w, i, j);
			if (--size == 0) goto done;
		}
	}
done:
	w.materials.emplace_back(new metal(vec3(0.8, 0.8, 0.8)));
	w.spheres.emplace_back(vec3(0, 1, 0), 1, w.materials.back().get());
	return w;
}
