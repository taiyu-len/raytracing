#ifndef COLOR_HPP
#define COLOR_HPP
#include "ray.hpp"
#include "vec3.hpp"
#include "world.hpp"

/**
 * @param[in]     hrs hit records for each ray
 * @param[in,out] ray set of rays, and new scattered rays
 * @param[in,out] colors color for each ray.
 * @todo add out param for generated rays.
 */
void color(
	std::vector<hit_record> const& hrs,
	std::vector<ray> & rays,
	std::vector<vec3> & attenuation);

#endif // COLOR_HPP
