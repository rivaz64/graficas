#include "camera.h"
#include<iostream>
camera::camera()
{
	viewmatrix = new float[16];
	proyectionmatrix = new float[16];
}
camera::~camera() {
	delete[] viewmatrix;
	delete[] proyectionmatrix;
}
void camera::gira(LPPOINT punto)
{
	if (!click) {
		click = true;
		p = punto;
        x = punto->x;
        y = punto->y;
	}
	else {

		at = zaxis + xaxis *(punto->x - x) * .003 - yaxis * (punto->y - y) * .003;

		at = at.normalize();
        x = punto->x;
        y = punto->y;
		at = at + eye;
		axis();
	}
}

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

void camera::movex(float x)
{
	
#ifdef directX
	eye = eye + xaxis * vel * x;
	at = at + xaxis * vel * x;
#endif
#ifdef openGL
	eye = eye - xaxis * vel * x;
	at = at - xaxis * vel * x;
#endif//*/
}

void camera::movey(float x)
{
	eye = eye + yaxis * vel * x;
	at = at + yaxis * vel * x;
}

void camera::movez(float x)
{
	eye = eye + zaxis * vel * x;
	at = at + zaxis * vel * x;
}


void camera::axis()
{
	vector3 dir = at - eye;
	zaxis = dir.normalize();
	xaxis = up.cross(zaxis).normalize();
	yaxis = zaxis.cross(xaxis);
}






void camera::getView(matrix& matrix)
{
#ifdef openGL
	matrix.m[0][0] = xaxis.x;
	matrix.m[0][1] = yaxis.x;
	matrix.m[0][2] = zaxis.x;
	matrix.m[0][3] = 0;
	matrix.m[1][0] = xaxis.y;
	matrix.m[1][1] = yaxis.y;
	matrix.m[1][2] = zaxis.y;
	matrix.m[1][3] = 0;
	matrix.m[2][0] = xaxis.z;
	matrix.m[2][1] = yaxis.z;
	matrix.m[2][2] = zaxis.z;
	matrix.m[2][3] = 0;
	matrix.m[3][0] = -xaxis.dot(eye);
	matrix.m[3][1] = -yaxis.dot(eye);
	matrix.m[3][2] = -zaxis.dot(eye);
	matrix.m[3][3] = 1;
#else
	matrix.m[0] = xaxis.x;
	matrix.m[4] = yaxis.x;
	matrix.m[8] = zaxis.x;
	matrix.m[12] = 0;
	matrix.m[1] = xaxis.y;
	matrix.m[5] = yaxis.y;
	matrix.m[9] = zaxis.y;
	matrix.m[13] = 0;
	matrix.m[2] = xaxis.z;
	matrix.m[6] = yaxis.z;
	matrix.m[10] = zaxis.z;
	matrix.m[14] = 0;
	matrix.m[3] = -xaxis.dot(eye);
	matrix.m[7] = -yaxis.dot(eye);
	matrix.m[11] = -zaxis.dot(eye);
	matrix.m[15] = 1;
		/*
	matrix.m[0] = xaxis.x;
	matrix.m[4] = yaxis.x;
	matrix.m[8] = zaxis.x;
	matrix.m[12] = 0;
	matrix.m[1] = xaxis.y;
	matrix.m[5] = yaxis.y;
	matrix.m[9] = zaxis.y;
	matrix.m[13] = 0;
	matrix.m[2] = xaxis.z;
	matrix.m[6] = yaxis.z;
	matrix.m[10] = zaxis.z;
	matrix.m[14] = 0;
	matrix.m[3] = -xaxis.dot(eye);
	matrix.m[7] = -yaxis.dot(eye);
	matrix.m[11] = -zaxis.dot(eye);
	matrix.m[15] = 1;*/
#endif
}

void camera::getProyectionMatrixPerspective(matrix& matrix)
{
	float co = cos(angle * .5f), s = sin(angle * .5f);
#ifdef openGL
	matrix.m[0][0] = (co / s) / ratio;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[0][3] = 0;
	matrix.m[1][0] = 0;
	matrix.m[1][1] = co / s;
	matrix.m[1][2] = 0;
	matrix.m[1][3] = 0;
	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = farp / (farp - nearp);
	matrix.m[2][3] = 1;
	matrix.m[3][0] = 0;
	matrix.m[3][1] = 0;
	matrix.m[3][2] = -farp * nearp / (farp - nearp);
	matrix.m[3][3] = 0;
#else
	
	matrix.m[0] = (co / s) / ratio;
	matrix.m[4] = 0;
	matrix.m[8] = 0;
	matrix.m[12] = 0;
	matrix.m[1] = 0;
	matrix.m[5] = co / s;
	matrix.m[9] = 0;
	matrix.m[13] = 0;
	matrix.m[2] = 0;
	matrix.m[6] = 0;
	matrix.m[10] = farp / (farp - nearp);
	matrix.m[14] = 1;
	matrix.m[3] = 0;
	matrix.m[7] = 0;
	matrix.m[11] = -farp * nearp / (farp - nearp);
	matrix.m[15] = 0;
#endif
}





float* camera::getproyectionmatrixOrtograpyc(float with, float height, float nearp, float farp)
{
	proyectionmatrix[0] = 2.0 / with;
	proyectionmatrix[1] = 0;
	proyectionmatrix[2] = 0;
	proyectionmatrix[3] = 0;
	proyectionmatrix[4] = 0;
	proyectionmatrix[5] = 2.0 / height;
	proyectionmatrix[6] = 0;
	proyectionmatrix[7] = 0;
	proyectionmatrix[8] = 0;
	proyectionmatrix[9] = 0;
	proyectionmatrix[10] = 1.f / (farp - nearp);
	proyectionmatrix[11] = 0;
	proyectionmatrix[12] = 0;
	proyectionmatrix[13] = 0;
	proyectionmatrix[14] = -nearp / (farp - nearp);
	proyectionmatrix[15] = 1;
	return proyectionmatrix;
}






