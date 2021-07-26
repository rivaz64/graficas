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


	struct ShaderResourseView {
#ifdef directX
		ID3D11ShaderResourceView* get;
#endif
#ifdef openGL
		unsigned int get;
#endif
	};


	class Textura
	{

	public:
		ShaderResourseView srv;
#ifdef directX
		ID3D11Texture2D* get = NULL;
		D3D11_TEXTURE2D_DESC des;
		
#endif
#ifdef openGL
		GLenum format= GL_TEXTURE_2D;
#endif
	public:
		void describe(FORMAT f, BIND_FLAG bf);
		void loadfromfile(LPCSTR f,int inverted, SRV_DIMENSION d);
		void init();
		void update(unsigned char*& bits, unsigned int pitch);
		void GenerateMips();
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


