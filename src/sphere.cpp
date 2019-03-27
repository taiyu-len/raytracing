#include "sphere.hpp"
[[nodiscard]]
static auto make_hitrecord(float t, ray r, sphere s) -> hit_record
{
	auto rec = hit_record{};
	rec.t = t;
	rec.p = r(rec.t);
	rec.n = (rec.p - s.center) / s.radius;
	rec.mat = s.mat;
	return rec;
}

auto sphere::hit(ray r, float tmin, float tmax) const
-> std::optional<hit_record>
{
	auto oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = dot(oc, r.direction());
	auto c = dot(oc, oc) - radius*radius;
	auto discriminant = b*b - a*c;
	if (discriminant > 0) {
		auto disc_sqrt = sqrt(b*b - a*c);
		auto temp = -(b + disc_sqrt) / a;
		if (temp < tmax && temp > tmin)
			return make_hitrecord(temp, r, *this);
		temp = (disc_sqrt - b) / a;
		if (temp < tmax && temp > tmin)
			return make_hitrecord(temp, r, *this);
	}
	return {};
}
