#include "camera.h"

void camera::seteye(float x, float y, float z)
{
	eye.x = x;
	eye.y = y;
	eye.z = z;
}

void camera::setat(float x, float y, float z)
{
	at.x = x;
	at.y = y;
	at.z = z;
}

void camera::setup(float x, float y, float z)
{
	up.x = x;
	up.y = y;
	up.z = z;
}

XMMATRIX camera::getviewmatrix()
{
	vector3 dir;
	dir.x = at.x - eye.x;
	dir.y = at.y - eye.y;
	dir.z = at.z - eye.z;
	vector3 zaxis = dir.normalize();
	vector3 xaxis = up.cross(zaxis).normalize();
	vector3 yaxis = zaxis.cross(xaxis);
	XMMATRIX viewmatrix;
	viewmatrix.m[0][0] = xaxis.x;
	viewmatrix.m[0][1] = yaxis.x;
	viewmatrix.m[0][2] = zaxis.x;
	viewmatrix.m[0][3] = 0;
	viewmatrix.m[1][0] = xaxis.y;
	viewmatrix.m[1][1] = yaxis.y;
	viewmatrix.m[1][2] = zaxis.y;
	viewmatrix.m[1][3] = 0;
	viewmatrix.m[2][0] = xaxis.z;
	viewmatrix.m[2][1] = yaxis.z;
	viewmatrix.m[2][2] = zaxis.z;
	viewmatrix.m[2][3] = 0;
	viewmatrix.m[3][0] = -xaxis.dot(eye);
	viewmatrix.m[3][1] = -yaxis.dot(eye);
	viewmatrix.m[3][2] = -zaxis.dot(eye);
	viewmatrix.m[3][3] = 1;


	//float viewmatrix[1][1] = { {1} };
	return viewmatrix;
}

XMMATRIX camera::getproyectionmatrixPerspective(float angle, float ratio, float nearp, float farp)
{
	float co = cos(angle * .5f), s = sin(angle * .5f);
	XMMATRIX proyection;
	proyection.m[0][0] = (co / s)/ratio;
	proyection.m[0][1] = 0;
	proyection.m[0][2] = 0;
	proyection.m[0][3] = 0;
	proyection.m[1][0] = 0;
	proyection.m[1][1] = co / s;
	proyection.m[1][2] = 0;
	proyection.m[1][3] = 0;
	proyection.m[2][0] = 0;
	proyection.m[2][1] = 0;
	proyection.m[2][2] = farp / (farp - nearp);
	proyection.m[2][3] = 1;
	proyection.m[3][0] = 0;
	proyection.m[3][1] = 0;
	proyection.m[3][2] = -farp*nearp / (farp - nearp);
	proyection.m[3][3] = 0;
	return proyection;
}

XMMATRIX camera::getproyectionmatrixOrtograpyc(float with, float height, float nearp, float farp)
{
	//float co = cos(angle * .5f), s = sin(angle * .5f);
	XMMATRIX proyection;
	proyection.m[0][0] = 2.0/with;
	proyection.m[0][1] = 0;
	proyection.m[0][2] = 0;
	proyection.m[0][3] = 0;
	proyection.m[1][0] = 0;
	proyection.m[1][1] = 2.0/height;
	proyection.m[1][2] = 0;
	proyection.m[1][3] = 0;
	proyection.m[2][0] = 0;
	proyection.m[2][1] = 0;
	proyection.m[2][2] = 1.f / (farp - nearp);
	proyection.m[2][3] = 0;
	proyection.m[3][0] = 0;
	proyection.m[3][1] = 0;
	proyection.m[3][2] = -nearp / (farp - nearp);
	proyection.m[3][3] = 1;
	return proyection;
}




