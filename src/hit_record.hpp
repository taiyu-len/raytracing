#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP
#include "vec3.hpp"
#include "ray.hpp"
#include <optional>

struct material;
struct hit_record {
	float t;
	vec3 p;
	vec3 n;
	material* mat;
};

template<typename I>
// requires Iterator<I>
// requires ValueType<I>::hit(ray(), float(), float()) ->
//   std::optional<hit_record>
auto hit_test(
	I first, I last,
	ray r, float tmin, float tmax,
	std::optional<hit_record> = std::nullopt
) -> std::optional<hit_record>;

#include "hit_record_t.hpp"
#endif // HIT_RECORD_HPP
