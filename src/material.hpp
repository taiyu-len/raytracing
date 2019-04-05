#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "ray.hpp"
#include "vec3.hpp"
#include "hit_record.hpp"
#include <optional>

struct material
{
	/**
	 * @param[in] ray the ray that hit this material
	 * @param[in] hit_record information about the interaction
	 * @param[in,out] attenuation the color of the ray
	 * @param[out] scatter the scattered ray
	 * @return true if the output paramters have been modified.
	 * @post   hit_record.mat != nullptr
	 */
	virtual
	bool scatter(
		ray,
		hit_record const&,
		vec3& attenuation,
		ray& scattered) const = 0;
	virtual ~material() = default;
};

struct lambertian : material {
	lambertian(vec3 a):albedo(a) {};
	bool scatter(
		ray,
		hit_record const&,
		vec3& attenuation,
		ray& scattered) const override;

	vec3 albedo;
};

struct metal : material {
	metal(vec3 a, float f=0):albedo(a), fuzz(f) {};

	bool scatter(
		ray,
		hit_record const&,
		vec3& attenuation,
		ray& scattered) const override;

	vec3 albedo;
	float fuzz;
};

struct dielectric : material {
	dielectric(float ri): ref_idx(ri) {};

	bool scatter(
		ray,
		hit_record const&,
		vec3& attenuation,
		ray& scattered) const override;

	float ref_idx;
};


#endif // MATERIAL_HPP
