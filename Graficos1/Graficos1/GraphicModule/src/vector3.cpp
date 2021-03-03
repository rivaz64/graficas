#include "vector3.h"
#include<cstdint>
#include <stdio.h>
#include <string.h>
#include <limits>
float Q_rsqrt(float number)
{
	float x2 = number * 0.5F, y = number;
	std::uint32_t i;
	memcpy(&i, &y, sizeof(float));
	i = 0x5f3759df - (i >> 1);
	memcpy(&y, &i, sizeof(float));
	return y * (1.5F - (x2 * y * y));
}
vector3 vector3::normalize()
{
	float d = Q_rsqrt(x * x + y * y + z * z);
	vector3 ans = *this;
	ans.x = x*d;
	ans.y = y*d;
	ans.z = z*d;
	return ans;

}

vector3 vector3::cross(vector3 v)
{
	vector3 ans;
	ans.x = y * v.z - z * v.y;
	ans.y = z * v.x - x * v.z;
	ans.z = x * v.y - y * v.x;
	return ans;
}

float vector3::dot(vector3 v)
{
	return x*v.x+y*v.y+z*v.z;
}
