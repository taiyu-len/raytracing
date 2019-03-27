ray::ray(vec3 x, vec3 y)
: s(x), t(y)
{}

auto ray::origin() const -> vec3
{
	return s;
}

auto ray::direction() const -> vec3
{
	return t;
}

auto ray::operator()(float x) const -> vec3
{
	return s + t*x;
}
