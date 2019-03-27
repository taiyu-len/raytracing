#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "ray.hpp"
#include "vec3.hpp"
#include "hit_record.hpp"
#include <optional>

struct material
{
	struct scatter_result {
		vec3 attenuation;
		ray  scattered;
	};
	virtual auto scatter(ray, hit_record const&) const
	-> std::optional<scatter_result> = 0;
};

struct lambertian : material {
	lambertian(vec3 a):albedo(a) {};

	auto scatter(ray r, hit_record const&record) const
	-> std::optional<scatter_result> override;

	vec3 albedo;
};

struct metal : material {
	metal(vec3 a, float f=0):albedo(a), fuzz(f) {};

	auto scatter(ray r, hit_record const&record) const
	-> std::optional<scatter_result> override;

	vec3 albedo;
	float fuzz;
};

struct dielectric : material {
	dielectric(float ri): ref_idx(ri) {};

	auto scatter(ray r, hit_record const&record) const
	-> std::optional<scatter_result> override;

	float ref_idx;
};


#endif // MATERIAL_HPP
