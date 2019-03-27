#ifndef RAY_HPP
#define RAY_HPP
#include "vec3.hpp"
struct ray {
	ray() = default;
	inline ray(vec3 x, vec3 y);
	[[nodiscard]] inline auto origin() const -> vec3;
	[[nodiscard]] inline auto direction() const -> vec3;
	[[nodiscard]] inline auto operator()(float t) const -> vec3;

	vec3 s, t;
};
#include "ray_t.hpp"
#endif // RAY_HPP
