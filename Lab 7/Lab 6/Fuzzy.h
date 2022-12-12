#ifndef FUZZY_H
#define FUZZY_H

#include <algorithm>

namespace fuzzy
{
	float grade(float t_value, float t_x0, float t_x1);
	float triangle(float t_value, float t_x0, float t_x1, float t_x2);
	float trapezoid(float t_value, float t_x0, float t_x1, float t_x2, float t_x3);

	float AND(float t_a, float t_b);
	float OR(float t_a, float t_b);
	float NOT(float t_a);
}

#endif // !FUZZY_H