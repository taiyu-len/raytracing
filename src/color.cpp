#include "color.hpp"
#include "rng.hpp"
#include <numeric>

static
auto color_hit(ray r, world const& w) -> std::optional<hit_record>
{
	return w.hit(r, 0.001, std::numeric_limits<float>::max());
}

static
auto bg_color(ray r) -> vec3
{
	auto unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1);
	return (1.0 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1.0);
}

auto color(ray r, world const& w) -> vec3
{
	auto max_iter = 50;
	auto attenuation = vec3(1, 1, 1);
	auto result = vec3();

	do {
		auto record = color_hit(r, w);
		if (record) {
			auto sr = record->mat->scatter(r, *record);
			if (sr) {
				attenuation *= sr->attenuation;
				r = sr->scattered;
			} else break;
		} else {
			result += attenuation * bg_color(r);
			break;
		}
	} while (attenuation.length_sq() > 0.001 && max_iter-- > 0);
	return result;
}
