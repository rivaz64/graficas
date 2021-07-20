#pragma once
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#include "mesh.h"
#include"Buffer.h"
#include"viewport.h"
#include"Textura.h"
#include"RenderTargetView.h"
#include "DepthStencil.h"
#include "VertexShader.h"
#include"InputLayout.h"
#include "SamplerState.h"
namespace GraphicsModule {
	class Device
	{
#ifdef directX
	public:
		HRESULT CreatePixelShader(ID3DBlob* pPSBlob, ID3D11PixelShader** pPixelShader);
		HRESULT CreateVS(ID3DBlob* Blob, VertexShader& vs);
	private:
		ID3D11Device* g_pd3dDevice = NULL;
#endif
	public:
#ifdef directX
		ID3D11Device* get() { return g_pd3dDevice; }
#else
		void get() {  }
#endif

#ifdef directX
		D3D11_TEXTURE2D_DESC descDepth;
		ID3D11RenderTargetView* g_pRenderTargetView;
		ID3D11DepthStencilView* DepthStencilView = NULL;
		ID3DBlob* pVSBlob;
		//ID3D11InputLayout* g_pVertexLayout;
		ID3D11ShaderResourceView* g_pTextureRV = NULL;
		//ID3D11SamplerState* g_pSamplerLinear = NULL;
#endif
		Buffer vertexB;
		Buffer indexB;
		Buffer neverChangesB;
		Buffer changesOnReziseB;
		Buffer changeveryFrameB;
		HWND g_hWndM;
		UINT width, height;
		HRESULT create(HWND g_hWnd);
#ifdef directX
		void createVSwithInput(ID3D11VertexShader** vs, ID3D11InputLayout** il, ID3DBlob* Blob);
#endif
		void CreateRenderTargetView(RenderTargetView& rtv,bool des,int n);
		void CreateTexture2D(Textura& tx);
		void CreateDepthStencilView(DepthStencil& ds);

		//HRESULT CreateInputLayout();


		void CreateShaderResourceViewFromFile(LPCSTR file);
		void CreateShaderResourceView(RenderTargetView& rtv,int n,SRV_DIMENSION d);
#ifdef directX
		void CreateBuffer(D3D11_BUFFER_DESC &bd, D3D11_SUBRESOURCE_DATA & InitData,Buffer &b);
#endif
		void CreateBuffer(Buffer& b);
		//void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT n, ID3DBlob* blob, InputLayout& il);
		void CreateSamplerState(SamplerState& ss);
		~Device();
		friend class manager;
	};
}


