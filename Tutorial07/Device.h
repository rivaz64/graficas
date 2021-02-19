#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "mesh.h"
struct CBNeverChanges
{
	XMMATRIX mView;
};

struct CBChangeOnResize
{
	XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
	XMMATRIX mWorld;
	XMFLOAT4 vMeshColor;
};
class Device
{
public:

	ID3D11Texture2D** deptstencil;
	D3D11_TEXTURE2D_DESC descDepth;
	ID3D11Device* g_pd3dDevice = NULL;
    ID3DBlob* pPSBlob = NULL;
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;
	ID3D11DepthStencilView* DepthStencilView=NULL;
	ID3DBlob* pVSBlob;
	ID3D11InputLayout* g_pVertexLayout;
	ID3D11Buffer* g_pVertexBuffer;
	ID3D11Buffer* g_pIndexBuffer;
	ID3D11Buffer* g_pCBNeverChanges = NULL;
	ID3D11Buffer* g_pCBChangeOnResize = NULL;
	ID3D11VertexShader* vertexshader=NULL;
	ID3D11Buffer* g_pCBChangesEveryFrame = NULL;
	ID3D11PixelShader* g_pPixelShader;
	ID3D11ShaderResourceView* g_pTextureRV = NULL;
	ID3D11SamplerState* g_pSamplerLinear = NULL;
	D3D11_BUFFER_DESC bd;
	HRESULT create(HWND g_hWnd,UINT width, UINT height);
	HRESULT CreateRenderTargetView(ID3D11Texture2D* idTextura);
	HRESULT CreateTexture2D(UINT width, UINT height, ID3D11Texture2D** DepthStencil);
	HRESULT CreateDepthStencilView();
	HRESULT CreateVertexShader(wchar_t* file, const char* vs, const char* vsv);
	HRESULT CreateInputLayout();
	HRESULT CreatePixelShader(wchar_t* file, const char* s, const char* sv);
	HRESULT CreateBuffer(mesh* m);
	void CreateShaderResourceViewFromFile(wchar_t* file);
	HRESULT CreateSamplerState();
	~Device();
};

