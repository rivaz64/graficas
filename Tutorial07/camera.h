#pragma once
#include"vector3.h"
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
class camera
{

public:
	vector3 eye, at, up;
	vector3 zaxis, yaxis, xaxis;
	LPPOINT p = new POINT;
	bool click = false;
	float vel=.001;
	void gira(LPPOINT punto);
	void seteye(float x, float y, float z);
	void setat(float x, float y, float z);
	void setup(float x, float y, float z);
	void axis();
	void movex(float x);
	void movey(float x);
	void movez(float x);
	XMMATRIX getviewmatrix();
	XMMATRIX getproyectionmatrixPerspective(float with,float ratio,float nearp,float farp);
	XMMATRIX getproyectionmatrixOrtograpyc(float with, float height, float nearp, float farp);
};

