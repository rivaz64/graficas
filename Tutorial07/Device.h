#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
class Device
{
public:

	ID3D11Texture2D** deptstencil;
	D3D11_TEXTURE2D_DESC descDepth;
	ID3D11Device* g_pd3dDevice = NULL;
	ID3D11RenderTargetView* const* g_pRenderTargetView = NULL;
	ID3D11DepthStencilView* DepthStencilView=NULL;
	HRESULT CreateRenderTargetView(ID3D11Texture2D* idTextura, ID3D11RenderTargetView** targetViews);
	HRESULT CreateTexture2D(UINT width, UINT height, ID3D11Texture2D** DepthStencil);
	HRESULT CreateDepthStencilView();
	HRESULT CreateVertexShader(wchar_t* file, const char* vs, const char* vsv, ID3D11VertexShader** vertexshader);
	~Device();
};

