#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "Textura.h"
#include <initializer_list>
namespace GraphicsModule {
	class RenderTargetView
	{
	public:
		ID3D11RenderTargetView* get = NULL;
		Textura textur;
		ID3D11ShaderResourceView* srv = NULL;
		float ClearColor[4]= { 0.0f, 0.125f, 0.3f, 1.0f };
		void setClearColor(std::initializer_list<float> c);
		void release();
	};
}


