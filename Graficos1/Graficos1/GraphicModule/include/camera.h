#pragma once
#include"vector3.h"
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#ifdef openGL
#include <glm/gtc/matrix_transform.hpp>
#endif
#include <array>
struct matrix
{
#ifdef openGL
	glm::mat4 m= glm::mat4(1.0f);
#else
	float m[16] = { 
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1, };
	//XMMATRIX m;
#endif
};
class camera
{

public:
	float angle, ratio, nearp, farp;
	vector3 eye, at, up;
	vector3 zaxis, yaxis, xaxis;
	LPPOINT p = new POINT;
	bool click = false;
	float* viewmatrix;
	float* proyectionmatrix;
	float vel = .001;
    float x, y;
	camera();
	~camera();
	void gira(LPPOINT punto);
	void seteye(float x, float y, float z);
	void setat(float x, float y, float z);
	void setup(float x, float y, float z);
	void axis();
	void movex(float x);
	void movey(float x);
	void movez(float x);

	void getView(matrix& matrix);
	void getProyectionMatrixPerspective(matrix& matrix);
	float* getproyectionmatrixOrtograpyc(float with, float height, float nearp, float farp);
};

