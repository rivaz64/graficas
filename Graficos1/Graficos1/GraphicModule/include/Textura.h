#pragma once
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#ifdef openGL
#include<glad\glad.h>
#define GLFW_INCLUDE_NONE
#include<glfw\glfw3.h>
#include<glfw\glfw3native.h>
#endif
#include"flags.h"
#include<string>
using std::string;
namespace GraphicsModule {
	class Textura
	{

	public:
#ifdef directX
		D3D11_TEXTURE2D_DESC des;
		ID3D11Texture2D* get=NULL;
		ID3D11ShaderResourceView* srv = NULL;
#else 
		unsigned int srv =0;
		GLenum format= GL_TEXTURE_2D;
#endif

		void describe(FORMAT f, BIND_FLAG bf);
		void loadfromfile(LPCSTR f,int inverted, SRV_DIMENSION d);
		//unsigned int loadCubemap(vector<std::string> faces);
		void release();
#ifdef openGL
		unsigned int
#endif
#ifdef directX
			ID3D11ShaderResourceView*
#endif
			geter();
	};
}


