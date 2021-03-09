#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
namespace GraphicsModule {
	class VertexShader
	{
	public:
#ifdef directX
		ID3D11VertexShader* g_pVertexShader = NULL;
#endif
	

#ifdef directX
		ID3D11VertexShader* get() { return g_pVertexShader; }
#else
		void get(){};
#endif
		~VertexShader() {
#ifdef directX
			if (g_pVertexShader) {
				g_pVertexShader->Release();
			}
#endif
		}
	};
}


