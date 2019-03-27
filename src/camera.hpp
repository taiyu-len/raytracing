#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "ray.hpp"
#include "vec3.hpp"
struct camera {
	// fov in degrees
	camera(
		vec3 lookfrom, vec3 lookat, vec3 vup,
		float vfov, float aspect, float aperture, float focus_dist);
	[[nodiscard]] auto operator()(float u, float v) const -> ray;

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lens_radius;
};
#endif // CAMERA_HPP
