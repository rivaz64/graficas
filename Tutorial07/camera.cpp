#include "camera.h"

void camera::gira(LPPOINT punto)
{
	/*vector3 dir = at - eye;
	vector3 zaxis = dir.normalize();
	vector3 xaxis = up.cross(zaxis).normalize();
	vector3 yaxis = zaxis.cross(xaxis);
	at = zaxis + xaxis * .001;//- yaxis * (punto->y - p->y) * .02;
	at = at.normalize();
	at = at + eye;
	p = punto;*/
	if (!click) {
		click = true;
		p = punto;
	}
	else {
		
		at = zaxis + xaxis * (punto->x - p->x) * .003 - yaxis * (punto->y - p->y) * .003;
		at = at.normalize();
		p = punto;
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
	eye = eye + xaxis * vel*x;
	at = at + xaxis * vel*x;
}
void camera::movey(float x)
{
	eye = eye + yaxis * vel * x;
	at = at + yaxis * vel * x;
}

void camera::movez(float x)
{
	eye = eye + zaxis * vel*x;
	at = at + zaxis * vel*x;
}


void camera::axis()
{
	vector3 dir = at - eye;
	 zaxis = dir.normalize();
	 xaxis = up.cross(zaxis).normalize();
	 yaxis = zaxis.cross(xaxis);
}



float* camera::getview() {
	float * mtrx = new float[16];
	mtrx[0] = xaxis.x;
	mtrx[1] = yaxis.x;
	mtrx[2] = zaxis.x;
	mtrx[3] = 0;
	mtrx[4] = xaxis.y;
	mtrx[5] = yaxis.y;
	mtrx[6] = zaxis.y;
	mtrx[7] = 0;
	mtrx[8] = xaxis.z;
	mtrx[9] = yaxis.z;
	mtrx[10] = zaxis.z;
	mtrx[11] = 0;
	mtrx[12] = -xaxis.dot(eye);
	mtrx[13] = -yaxis.dot(eye);
	mtrx[14] = -zaxis.dot(eye);
	mtrx[15] = 1;
	viewmatrix = mtrx;
	return viewmatrix;
}

float* camera::getproyectionmatrixPerspective(float angle, float ratio, float nearp, float farp)
{
	float co = cos(angle * .5f), s = sin(angle * .5f);
	float* mtrx = new float[16];
	mtrx[0] = (co / s) / ratio;
	mtrx[1] = 0;
	mtrx[2] = 0;
	mtrx[3] = 0;
	mtrx[4] = 0;
	mtrx[5] = co / s;
	mtrx[6] = 0;
	mtrx[7] = 0;
	mtrx[8] = 0;
	mtrx[9] = 0;
	mtrx[10] = farp / (farp - nearp);
	mtrx[11] = 1;
	mtrx[12] = 0;
	mtrx[13] = 0;
	mtrx[14] = -farp * nearp / (farp - nearp);
	mtrx[15] = 0;
	return mtrx;
}

float* camera::getproyectionmatrixOrtograpyc(float with, float height, float nearp, float farp)
{
	float* mtrx = new float[16];
	mtrx[0] = 2.0 / with;
	mtrx[1] = 0;
	mtrx[2] = 0;
	mtrx[3] = 0;
	mtrx[4] = 0;
	mtrx[5] = 2.0 / height;
	mtrx[6] = 0;
	mtrx[7] = 0;
	mtrx[8] = 0;
	mtrx[9] = 0;
	mtrx[10] = 1.f / (farp - nearp);
	mtrx[11] = 0;
	mtrx[12] = 0;
	mtrx[13] = 0;
	mtrx[14] = -nearp / (farp - nearp);
	mtrx[15] = 1;
	return mtrx;
}




