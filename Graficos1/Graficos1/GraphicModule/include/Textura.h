#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>}
#include"flags.h"
namespace GraphicsModule {
	class Textura
	{
		
	public:
		D3D11_TEXTURE2D_DESC des;
		ID3D11Texture2D* get;
		void describe(FORMAT f, BIND_FLAG bf);
	};
}


