#pragma once
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#include <vector>
namespace GraphicsModule
{
	class PixelShader
	{
	public:
		int cual;
#ifdef directX
		ID3D11PixelShader* g_pPixelShader = NULL;

#endif
	public:
#ifdef directX
		ID3D11PixelShader* get() {
			return g_pPixelShader;
		}
#else
		void get() {}
#endif

	};

}


