#ifndef WORLD_HPP
#define WORLD_HPP
#include "hit_record.hpp"
#include "material.hpp"
#include <optional>
#include <memory>
#include <vector>

struct world : hitable {
	std::vector<std::unique_ptr<hitable>>  objects;
	std::vector<std::unique_ptr<material>> materials;

	template<typename T, typename... Args>
	void add_object(Args&&... args)
	{
		auto o = std::make_unique<T>(std::forward<Args>(args)...);
		objects.push_back(std::move(o));
	}
	void operator()(ray const*, float*, hit_record*, size_t) const override;
};

auto make_world(int size) -> world;

#endif // WORLD_HPP
