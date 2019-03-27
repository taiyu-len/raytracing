#ifndef RNG_HPP
#define RNG_HPP
#include "vec3.hpp"
[[nodiscard]] auto rng(float min = 0, float max = 1) -> float;
[[nodiscard]] auto random_vec_in_unit_sphere() -> vec3;
#endif // RNG_HPP
