#include "color.hpp"
#include "rng.hpp"
#include <numeric>

static
auto bg_color(ray r) -> vec3
{
	auto unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1);
	return (1.0 - t) * vec3{1, 1, 1} + t * vec3{0.5, 0.7, 1.0};
}

void color(
	std::vector<hit_record> const& hrs,
	std::vector<ray>& rays,
	std::vector<vec3>& colors)
{
	for (auto i = 0u; i < hrs.size(); ++i) {
		if (! hrs[i].mat) {
			colors[i] *= bg_color(rays[i]);
		} else if (hrs[i].mat->scatter(rays[i], hrs[i], colors[i], rays[i])) {
		} else {
			colors[i] = vec3{0, 0, 0};
		}
	}
}

