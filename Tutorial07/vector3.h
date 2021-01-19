#pragma once
class vector3
{
public:
	float x, y, z;
	vector3(float X, float Y, float Z):x(X),y(Y),z(Z){}
	vector3():x(0),y(0),z(0) {}

	vector3 normalize();
	vector3 cross(vector3 v);
	float dot(vector3 v);
};

