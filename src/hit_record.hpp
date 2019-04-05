#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP
#include "vec3.hpp"
#include "ray.hpp"
#include <optional>

struct material;

struct hit_record {
	hit_record(vec3 p, vec3 n, material* m):p(p), normal(n), mat(m) {};
	hit_record():mat(nullptr) {};

	vec3 p, normal;
	material* mat = nullptr;
	operator bool() const { return mat; }
};

struct hitable {
	virtual
	void operator()(
		ray const* first /* in     */,
		float* t_best    /* in,out */,
		hit_record* hr   /*    out */,
		size_t count) const = 0;
	virtual ~hitable() = default;
};

#endif // HIT_RECORD_HPP
