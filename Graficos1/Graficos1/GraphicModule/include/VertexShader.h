#pragma once
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
namespace GraphicsModule {
	class VertexShader
	{
	public:
#ifdef directX
		ID3D11VertexShader* g_pVertexShader = NULL;
#endif
		unsigned int shader;

#ifdef directX
		ID3D11VertexShader* get() { return g_pVertexShader; }
#else
		unsigned int get() { return shader; }
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


