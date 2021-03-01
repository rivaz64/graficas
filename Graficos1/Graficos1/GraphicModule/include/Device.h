#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "mesh.h"
#include"Buffer.h"
#include"viewport.h"
#include"Textura.h"


class Device
{
public:
    Textura depstencil;
	//ID3D11Texture2D** deptstencil;
	D3D11_TEXTURE2D_DESC descDepth;
	ID3D11Device* g_pd3dDevice = NULL;
    
    viewport vp;
	ID3D11DepthStencilView* DepthStencilView=NULL;
	ID3DBlob* pVSBlob;
	ID3D11InputLayout* g_pVertexLayout;
    Buffer vertexB;
    Buffer indexB;
    Buffer neverChangesB;
    Buffer changesOnReziseB;
    Buffer changeveryFrameB;
	ID3D11VertexShader* vertexshader=NULL;
	ID3D11PixelShader* g_pPixelShader;
	ID3D11ShaderResourceView* g_pTextureRV = NULL;
	ID3D11SamplerState* g_pSamplerLinear = NULL;
	D3D11_BUFFER_DESC bd;
    D3D11_SUBRESOURCE_DATA InitData;
	HWND g_hWndM;
	UINT width, height;
	HRESULT create(HWND g_hWnd);
	HRESULT CreateRenderTargetView(ID3D11Texture2D* idTextura);
	HRESULT CreateTexture2D();
	HRESULT CreateDepthStencilView();
	HRESULT CreateVertexShader(ID3DBlob* pPSBlob);
	HRESULT CreateInputLayout();
	HRESULT CreatePixelShader(ID3DBlob* pPSBlob);
	HRESULT CreateBuffers();
    void setmesh(mesh* m);
	void CreateShaderResourceViewFromFile(LPCSTR file);
	HRESULT CreateSamplerState();
	~Device();
};

