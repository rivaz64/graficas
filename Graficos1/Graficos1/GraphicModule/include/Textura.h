#pragma once
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
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
		ID3D11Texture2D* get;
		ID3D11ShaderResourceView* srv;
#else 
		unsigned int get;
		#endif
		
		void describe(FORMAT f, BIND_FLAG bf);
		void loadfromfile(LPCSTR f);
		void release();
	};
}


