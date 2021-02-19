#include "camera.h"

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

		at = zaxis + xaxis * (punto->x - x) * .003 - yaxis * (punto->y - y) * .003;
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
	eye = eye + xaxis * vel * x;
	at = at + xaxis * vel * x;
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



float* camera::getview() {
    axis();
	viewmatrix[0] = xaxis.x;
	viewmatrix[1] = yaxis.x;
	viewmatrix[2] = zaxis.x;
	viewmatrix[3] = 0;
	viewmatrix[4] = xaxis.y;
	viewmatrix[5] = yaxis.y;
	viewmatrix[6] = zaxis.y;
	viewmatrix[7] = 0;
	viewmatrix[8] = xaxis.z;
	viewmatrix[9] = yaxis.z;
	viewmatrix[10] = zaxis.z;
	viewmatrix[11] = 0;
	viewmatrix[12] = -xaxis.dot(eye);
	viewmatrix[13] = -yaxis.dot(eye);
	viewmatrix[14] = -zaxis.dot(eye);
	viewmatrix[15] = 1;
	return viewmatrix;
}

float* camera::getproyectionmatrixPerspective(float angle, float ratio, float nearp, float farp)
{
	float co = cos(angle * .5f), s = sin(angle * .5f);

	proyectionmatrix[0] = (co / s) / ratio;
	proyectionmatrix[1] = 0;
	proyectionmatrix[2] = 0;
	proyectionmatrix[3] = 0;
	proyectionmatrix[4] = 0;
	proyectionmatrix[5] = co / s;
	proyectionmatrix[6] = 0;
	proyectionmatrix[7] = 0;
	proyectionmatrix[8] = 0;
	proyectionmatrix[9] = 0;
	proyectionmatrix[10] = farp / (farp - nearp);
	proyectionmatrix[11] = 1;
	proyectionmatrix[12] = 0;
	proyectionmatrix[13] = 0;
	proyectionmatrix[14] = -farp * nearp / (farp - nearp);
	proyectionmatrix[15] = 0;
	return proyectionmatrix;
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






