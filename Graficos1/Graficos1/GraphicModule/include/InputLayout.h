#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
namespace GraphicsModule {
	class InputLayout
	{
	public:
#ifdef directX
		ID3D11InputLayout* g_pVertexLayout = NULL;
#endif
		~InputLayout() {
#ifdef directX
			if (g_pVertexLayout) {
				g_pVertexLayout->Release();
			}
#endif
		}
	};
}

