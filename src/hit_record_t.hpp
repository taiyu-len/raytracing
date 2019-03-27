template<typename I>
auto hit_test(
	I first, I last,
	ray r, float tmin, float tmax,
	std::optional<hit_record> best
) -> std::optional<hit_record>
{
	float closest = best ? best->t : tmax;
	for (; first != last; ++first) {
		auto test = first->hit(r, tmin, closest);
		if (test) {
			best = test;
			closest = best->t;
		}
	}
	return best;
}

