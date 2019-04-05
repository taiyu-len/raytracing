#ifndef VEC3_HPP
#define VEC3_HPP
#include <optional>

struct vec3 {
	[[nodiscard]] inline auto x() const -> float;
	[[nodiscard]] inline auto y() const -> float;
	[[nodiscard]] inline auto z() const -> float;

	[[nodiscard]] inline auto r() const -> float;
	[[nodiscard]] inline auto g() const -> float;
	[[nodiscard]] inline auto b() const -> float;

	[[nodiscard]] inline auto operator[](int i) const -> float;
	[[nodiscard]] inline auto operator[](int i) -> float&;

	[[nodiscard]] inline auto operator+() const -> const vec3&;
	[[nodiscard]] inline auto operator-() const -> vec3;

	inline auto operator+=(vec3 const&) -> vec3&;
	inline auto operator-=(vec3 const&) -> vec3&;
	inline auto operator*=(vec3 const&) -> vec3&;
	inline auto operator/=(vec3 const&) -> vec3&;
	inline auto operator*=(float x) -> vec3&;
	inline auto operator/=(float x) -> vec3&;


	[[nodiscard]] inline auto length() const -> float;
	[[nodiscard]] inline auto length_sq() const -> float;

	inline void make_unit_vector();

	float e0, e1, e2;
};

[[nodiscard]] inline auto operator+(vec3 x, vec3 const& y) -> vec3;
[[nodiscard]] inline auto operator-(vec3 x, vec3 const& y) -> vec3;
[[nodiscard]] inline auto operator*(vec3 x, vec3 const& y) -> vec3;
[[nodiscard]] inline auto operator/(vec3 x, vec3 const& y) -> vec3;
[[nodiscard]] inline auto operator*(vec3 x, float const& y) -> vec3;
[[nodiscard]] inline auto operator/(vec3 x, float const& y) -> vec3;
[[nodiscard]] inline auto operator*(float const& x, vec3 y) -> vec3;
[[nodiscard]] inline auto operator/(float const& x, vec3 y) -> vec3;

[[nodiscard]] inline auto dot(vec3, vec3) -> float;
[[nodiscard]] inline auto cross(vec3, vec3) -> vec3;
[[nodiscard]] inline auto reflect(vec3, vec3) -> vec3;
[[nodiscard]] inline auto refract(vec3, vec3, float) -> std::optional<vec3>;
[[nodiscard]] inline auto sqrt(vec3) -> vec3;

[[nodiscard]] inline auto unit_vector(vec3 x) -> vec3;

#include "vec3_t.hpp"
#endif // VEC3_HPP
