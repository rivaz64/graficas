#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "mesh.h"
class Device
{
public:

	ID3D11Texture2D** deptstencil;
	D3D11_TEXTURE2D_DESC descDepth;
	ID3D11Device* g_pd3dDevice = NULL;
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;
	ID3D11DepthStencilView* DepthStencilView=NULL;
	ID3DBlob* pVSBlob;
	ID3D11InputLayout* g_pVertexLayout;
	ID3D11Buffer* g_pVertexBuffer;
	ID3D11Buffer* g_pIndexBuffer;
	HRESULT CreateRenderTargetView(ID3D11Texture2D* idTextura);
	HRESULT CreateTexture2D(UINT width, UINT height, ID3D11Texture2D** DepthStencil);
	HRESULT CreateDepthStencilView();
	HRESULT CreateVertexShader(wchar_t* file, const char* vs, const char* vsv);
	HRESULT CreateInputLayout();
	HRESULT CreatePixelShader(wchar_t* file, const char* s, const char* sv);
	HRESULT CreateBuffer(mesh* m);
	~Device();
};

