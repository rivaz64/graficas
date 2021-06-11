#pragma once
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#include "flags.h"
namespace GraphicsModule {
	class Rasterizer
	{
#ifdef directX
		ID3D11RasterizerState* g_Rasterizer = NULL;
#endif
		CULING c;
	public:
		void create(CULING cul);
		void setear();
	};
}


