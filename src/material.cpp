#include "material.hpp"
#include "rng.hpp"

bool lambertian::scatter(
	ray r,
	hit_record const& record,
	vec3& attenuation,
	ray& scattered
) const {
	vec3 target = record.p + record.normal + random_vec_in_unit_sphere();
	attenuation *= albedo;
	scattered = ray(record.p, target - record.p);
	return true;
}

bool metal::scatter(
	ray r,
	hit_record const& record,
	vec3& attenuation,
	ray& scattered
) const {
	vec3 reflected = reflect(unit_vector(r.direction()), record.normal);
	if (fuzz > 0.001) {
		auto rv = random_vec_in_unit_sphere();
		scattered = ray(record.p, reflected + fuzz*rv);
	} else {
		scattered = ray(record.p, reflected);
	}
	if (dot(scattered.direction(), record.normal) > 0) {
		attenuation *= albedo;
		return true;
	} else {
		return false;
	}
}

static auto shlick(float cosine, float ref_idx) -> float
{
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 *= r0;
	return r0 + (1 - r0)*pow(1-cosine, 5);
}

bool dielectric::scatter(
	ray r,
	hit_record const& record,
	vec3& attenuation,
	ray& scatter
) const {
	auto outward_normal = vec3();
	auto reflect_prob = float();
	auto ni_over_nt = float();
	auto cosine = float();
	const auto drn = dot(r.direction(), record.normal);

	if (drn > 0) {
		// inside
		outward_normal = -record.normal;
		ni_over_nt = ref_idx;
		cosine = ref_idx * drn;
	} else {
		// outside
		outward_normal = record.normal;
		ni_over_nt = 1.0 / ref_idx;
		cosine = -drn;
	}
	cosine /=  r.direction().length();

	auto refracted = refract(r.direction(), outward_normal, ni_over_nt);
	if (refracted) {
		reflect_prob = shlick(cosine, ref_idx);
	} else {
		reflect_prob = 2.0;
	}
	if (rng() < reflect_prob) {
		auto reflected = reflect(r.direction(), record.normal);
		scatter = ray(record.p, reflected);
	} else {
		scatter = ray(record.p, *refracted);
	}
	return true;
}
