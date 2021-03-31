#pragma once
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#include "Textura.h"
#include <initializer_list>
namespace GraphicsModule {
	class RenderTargetView
	{
	public:
#ifdef directX
		ID3D11RenderTargetView* get = NULL;
		ID3D11ShaderResourceView* srv = NULL;
#endif
		Textura textur;
		float ClearColor[4]= { 0.0f, 0.125f, 0.3f, 1.0f };
		void setClearColor(std::initializer_list<float> c);
		void release();
	};
}


