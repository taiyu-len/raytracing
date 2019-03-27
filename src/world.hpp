#ifndef WORLD_HPP
#define WORLD_HPP
#include "hit_record.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include <optional>
#include <memory>
#include <vector>

struct world {
	std::vector<sphere> spheres;
	std::vector<std::unique_ptr<material>> materials;
	[[nodiscard]] auto hit(
		ray r, float tmin, float tmax
	) const -> std::optional<hit_record>;
};

auto make_world() -> world;

#endif // WORLD_HPP
