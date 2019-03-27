#include <cmath>

vec3::vec3(float e0, float e1, float e2)
: e{e0, e1, e2}
{}

auto vec3::x() const -> float
{
	return (*this)[0];
}

auto vec3::y() const -> float
{
	return (*this)[1];
}

auto vec3::z() const -> float
{
	return (*this)[2];
}

auto vec3::r() const -> float
{
	return (*this)[0];
}

auto vec3::g() const -> float
{
	return (*this)[1];
}

auto vec3::b() const -> float
{
	return (*this)[2];
}

auto vec3::operator[](int i) const -> float
{
	return e[i];
}

auto vec3::operator[](int i) -> float&
{
	return e[i];
}

auto vec3::operator+() const -> const vec3&
{
	return *this;
}

auto vec3::operator-() const -> vec3
{
	return vec3(-e[0], -e[1], -e[2]);
}

auto vec3::operator+=(vec3 const& x) -> vec3&
{
	e[0] += x[0];
	e[1] += x[1];
	e[2] += x[2];
	return *this;
}

auto vec3::operator-=(vec3 const& x) -> vec3&
{
	e[0] -= x[0];
	e[1] -= x[1];
	e[2] -= x[2];
	return *this;
}

auto vec3::operator*=(vec3 const& x) -> vec3&
{
	e[0] *= x[0];
	e[1] *= x[1];
	e[2] *= x[2];
	return *this;
}

auto vec3::operator/=(vec3 const& x) -> vec3&
{
	e[0] /= x[0];
	e[1] /= x[1];
	e[2] /= x[2];
	return *this;
}

auto vec3::operator*=(float x) -> vec3&
{
	e[0] *= x;
	e[1] *= x;
	e[2] *= x;
	return *this;
}

auto vec3::operator/=(float x) -> vec3&
{
	e[0] /= x;
	e[1] /= x;
	e[2] /= x;
	return *this;
}

auto vec3::length() const -> float
{
	return std::sqrt(length_sq());
}

auto vec3::length_sq() const -> float
{
	return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

void vec3::make_unit_vector()
{
	*this *= 1.0 / length();
}

auto operator+(vec3 x, vec3 const& y) -> vec3
{
	return x += y;
}

auto operator-(vec3 x, vec3 const& y) -> vec3
{
	return x -= y;
}

auto operator*(vec3 x, vec3 const& y) -> vec3
{
	return x *= y;
}

auto operator/(vec3 x, vec3 const& y) -> vec3
{
	return x /= y;
}

auto operator*(vec3 x, float const& y) -> vec3
{
	return x *= y;
}

auto operator/(vec3 x, float const& y) -> vec3
{
	return x /= y;
}

auto operator*(float const& x, vec3 y) -> vec3
{
	return y *= x;
}

auto operator/(float const& x, vec3 y) -> vec3
{
	return y /= x;
}

auto dot(vec3 x, vec3 y) -> float
{
	return x[0]*y[0] + x[1]*y[1] + x[2]*y[2];
}

auto cross(vec3 x, vec3 y) -> vec3
{
	return vec3(
		x[1]*y[2] - x[2]*y[1],
		x[2]*y[0] - x[0]*y[2],
		x[0]*y[1] - x[1]*y[0]);
}

auto reflect(vec3 v, vec3 n) -> vec3
{
	return v - 2*dot(v, n)*n;
}

auto refract(vec3 v, vec3 n, float ni_over_nt) -> std::optional<vec3>
{
	auto uv = unit_vector(v);
	auto dt = dot(uv, n);
	auto discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
	if (discriminant > 0)
		return ni_over_nt * (uv - n*dt) - n*sqrt(discriminant);
	else return {};
}

auto sqrt(vec3 v) -> vec3
{
	return vec3(sqrt(v[0]), sqrt(v[1]), sqrt(v[2]));
}

auto unit_vector(vec3 x) -> vec3
{
	x.make_unit_vector();
	return x;
}
