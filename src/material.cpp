#include "material.hpp"
#include "rng.hpp"

auto lambertian::scatter(ray r, hit_record const& record) const
-> std::optional<scatter_result>
{
	vec3 target = record.p + record.n + random_vec_in_unit_sphere();
	return scatter_result{
		albedo,
		ray(record.p, target - record.p)
	};
}

auto metal::scatter(ray r, hit_record const& record) const
-> std::optional<scatter_result>
{
	vec3 reflected = reflect(unit_vector(r.direction()), record.n);
	auto scattered = ray(
		record.p,
		reflected + fuzz*random_vec_in_unit_sphere());
	if (dot(scattered.direction(), record.n) > 0) {
		return scatter_result{ albedo, scattered };
	} else {
		return {};
	}
}

static auto shlick(float cosine, float ref_idx) -> float
{
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 *= r0;
	return r0 + (1 - r0)*pow(1-cosine, 5);
}

auto dielectric::scatter(ray r, hit_record const& record) const
-> std::optional<scatter_result>
{
	auto outward_normal = vec3();
	auto attenuation = vec3(1, 1, 1);
	auto reflect_prob = float();
	auto ni_over_nt = float();
	auto cosine = float();

	if (dot(r.direction(), record.n) > 0) {
		outward_normal = -record.n;
		ni_over_nt = ref_idx;
		cosine = ref_idx * dot(r.direction(), record.n);
	} else {
		outward_normal = record.n;
		ni_over_nt = 1.0 / ref_idx;
		cosine = -dot(r.direction(), record.n);
	}
	cosine /=  r.direction().length();

	auto refracted = refract(r.direction(), outward_normal, ni_over_nt);
	if (refracted) {
		reflect_prob = shlick(cosine, ref_idx);
	} else {
		reflect_prob = 2.0;
	}
	if (rng() < reflect_prob) {
		auto reflected = reflect(r.direction(), record.n);
		return scatter_result{ attenuation, ray(record.p, reflected) };
	} else {
		return scatter_result{ attenuation, ray(record.p, *refracted) };
	}
}
