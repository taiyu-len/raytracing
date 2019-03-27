#include "camera.hpp"
#include "rng.hpp"
#include <cmath>
static
auto random_vec_in_unit_disk() -> vec3
{
	auto p = vec3();
	do {
		p = 2.0 * vec3(rng(), rng(), 0) - vec3(1,1,0);
	} while (dot(p, p) >= 1.0);
	return p;
}

camera::camera(
	vec3 lookfrom, vec3 lookat, vec3 vup,
	float vfov, float aspect, float aperture, float focus_dist)
{
	auto theta = vfov * M_PI / 180;
	auto half_height = tan(theta/2);
	auto half_width  = aspect * half_height;

	lens_radius = aperture / 2;
	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);

	origin = lookfrom;
	lower_left_corner = origin;
	lower_left_corner -= focus_dist*(u*half_width + v*half_height + w);
	horizontal = 2*half_width*focus_dist*u;
	vertical = 2*half_height*focus_dist*v;
};
auto camera::operator()(float s, float t) const -> ray
// [[ expects: u >= 0 && u < 1 ]]
// [[ expects: v >= 0 && v < 1 ]]
{
	auto rd = lens_radius * random_vec_in_unit_disk();
	auto offset = u * rd.x() + v * rd.y();
	return ray(
		origin + offset,
		lower_left_corner + s*horizontal + t*vertical - origin - offset);
}

