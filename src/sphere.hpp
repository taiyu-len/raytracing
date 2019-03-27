#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "vec3.hpp"
#include "ray.hpp"
#include "hit_record.hpp"
#include "material.hpp"
#include <optional>

struct sphere {
	sphere() = default;
	sphere(vec3 c, float r, material* m):center(c), radius(r), mat(m) {}
	auto hit(ray r, float tmin, float tmax) const -> std::optional<hit_record>;

	vec3  center;
	float radius;
	material* mat;
};

#endif // SPHERE_HPP
