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
#include "flags.h"
#include <vector>
namespace GraphicsModule {
	class RenderTargetView
	{
	public:
#ifdef directX
		std::vector<ID3D11RenderTargetView*> get;
		std::vector < ID3D11ShaderResourceView*> srv;
#endif
#ifdef openGL
		std::vector<unsigned int> srv;
#endif
		FORMAT Format;
		DIMENSION ViewDimension;
		UINT MostDetailedMip;
		UINT MipLevels;
		std::vector<Textura> textur;
		float ClearColor[4]= { 0.0f, 0.125f, 0.3f, 1.0f };
		void setClearColor(std::initializer_list<float> c);
		void release();
	};
}


