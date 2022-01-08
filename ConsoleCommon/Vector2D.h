#pragma once
#include <type_traits>

template <
	typename num_type,
	typename = typename std::enable_if<std::is_arithmetic<num_type>::value, num_type>::type>
class Vector2D
{
public:
	num_type x = 0, y = 0;

	Vector2D() {}
	Vector2D(num_type x0, num_type y0) : x(x0), y(y0) {}
};
