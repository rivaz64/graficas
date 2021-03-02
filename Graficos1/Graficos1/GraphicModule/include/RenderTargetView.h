#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "Textura.h"
namespace GraphicsModule {
	class RenderTargetView
	{
	public:
		ID3D11RenderTargetView* get = NULL;
		Textura textur;
		ID3D11ShaderResourceView* srv = NULL;
	};
}


