#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
namespace GraphicsModule {
	class SamplerState
	{
#ifdef directX
		ID3D11SamplerState* g_pSamplerLinear = NULL;
#endif
	public:
#ifdef directX
		ID3D11SamplerState* get() {
			return g_pSamplerLinear;
		}
#else
		void get() {}
#endif

	};
}

