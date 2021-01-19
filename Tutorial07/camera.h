#pragma once
#include"vector3.h"
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
class camera
{
	vector3 eye,at,up;
public:
	void seteye(float x, float y, float z);
	void setat(float x, float y, float z);
	void setup(float x, float y, float z);
	XMMATRIX getviewmatrix();
	XMMATRIX getproyectionmatrixPerspective(float with,float ratio,float nearp,float farp);
	XMMATRIX getproyectionmatrixOrtograpyc(float with, float height, float nearp, float farp);
};

