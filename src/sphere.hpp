#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "vec3.hpp"
#include "ray.hpp"
#include "hit_record.hpp"
#include "material.hpp"

struct sphere : hitable {
	sphere() = default;
	sphere(vec3 origin, float radius, material* mat)
	: origin(origin)
	, radius(radius)
	, mat(mat) {}

	void operator()(ray const*, float*, hit_record*, size_t) const override;

	vec3  origin;
	float radius;
	material* mat;
};

#endif // SPHERE_HPP
