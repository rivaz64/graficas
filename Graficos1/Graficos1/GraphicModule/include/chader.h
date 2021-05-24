#pragma once
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#include <string>
namespace GraphicsModule {
	class chader
	{

#ifdef directX
		ID3D11InputLayout* il;
		ID3D11VertexShader* VertexShader = NULL;
		ID3D11PixelShader* PixelShader = NULL;
#endif
	public:
		void compile(std::string file, std::string tecnique);
		void setShader();
	};
}