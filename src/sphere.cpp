#include "sphere.hpp"

void sphere::operator()(
	ray const* rs, float* ts, hit_record* hrs, size_t count) const
{
	auto last = rs + count;
	const auto set_hr = [&](float f) -> bool {
		if (f < *ts && f > 0.001) {
			auto p = (*rs)(f);
			*ts = f;
			*hrs = hit_record(p, (p - origin) / radius, mat);
			return true;
		} else return false;
	};
	while (rs != last) {
		auto oc = rs->origin() - origin;
		auto a = dot(rs->direction(), rs->direction());
		auto b = dot(oc, rs->direction());
		auto c = dot(oc, oc) - radius * radius;
		auto disc = b*b - a*c;
		// if we make contact, we check if its closer then previous
		// hits.
		if (disc > 0) {
			auto ds = sqrt(disc);
			if (!set_hr(-(b + ds) / a))
				set_hr((ds - b) / a);
		}
		++rs;
		++ts;
		++hrs;
	}
}
