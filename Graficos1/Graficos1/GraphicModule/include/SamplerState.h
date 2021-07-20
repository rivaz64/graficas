#pragma once

#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
namespace GraphicsModule {
	class SamplerState
	{
	public:
#ifdef directX
		ID3D11SamplerState* get = NULL;
		D3D11_SAMPLER_DESC desc;
#endif

	};
}

