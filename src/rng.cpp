#include <random>
#include "rng.hpp"

auto rng(float min, float max) -> float
{
	static auto rd = std::random_device();
	static auto gen = std::mt19937();
	return std::uniform_real_distribution<float>(min, max)(gen);
}

auto random_vec_in_unit_sphere() -> vec3
{
	auto p = vec3{};
	do {
		p = 2.0 * vec3(rng(), rng(), rng()) - vec3(1, 1, 1);
	} while (p.length_sq() >= 1.0);
	return p;
}
