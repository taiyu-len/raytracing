#ifndef PLANE_HPP
#define PLANE_HPP
#include "vec3.hpp"
#include "ray.hpp"
#include "hit_record.hpp"
#include "material.hpp"

struct plane : hitable {
	plane(vec3 normal, vec3 p0, material* mat)
	: normal(normal)
	, p0(p0)
	, mat(mat) {}

	void operator()(ray const*, float*, hit_record*, size_t) const override;

	vec3 normal;
	vec3 p0;
	material* mat;
};

#endif // PLANE_HPP
