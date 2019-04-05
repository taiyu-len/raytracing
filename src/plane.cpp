#include "plane.hpp"

void plane::operator()(
	ray const* rs,
	float* ts,
	hit_record* hrs,
	size_t count
) const {
	auto last = rs + count;
	while (rs != last) {
		auto r = *rs;
		auto denom = dot(normal, r.direction());
		// dont hit if ray is nearly parallel.
		if (denom > 1e-6) {
			// get vector p0 - r.origin()
			auto p0r0 = p0 - r.origin();
			// get distance from ray origin to plane along
			// ray direction
			auto t = dot(p0r0, normal) / denom;
			if (t >= 1e-6 && t < *ts) {
				*ts = t;
				*hrs = hit_record(r(t), -normal, mat);
			}
		}
		++rs;
		++ts;
		++hrs;
	}
}

