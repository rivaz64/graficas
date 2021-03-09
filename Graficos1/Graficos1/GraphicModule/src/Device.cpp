#include "Device.h"
#include"DeviceContext.h"
#include "SwapChain.h"
#include"test.h"
namespace GraphicsModule {
	HRESULT Device::create(HWND g_hWnd)
	{
		RECT rc;
		g_hWndM = g_hWnd;
		GetClientRect(g_hWnd, &rc);
		width = rc.right - rc.left;
		height = rc.bottom - rc.top;
		return S_OK;
	}
	void Device::CreateRenderTargetView(RenderTargetView& rtv)
	{
#ifdef directX
		 g_pd3dDevice->CreateRenderTargetView(rtv.textur.get, NULL, &rtv.get);
#endif
	}

	void Device::CreateTexture2D(Textura& tx)
	{
#ifdef directX
		g_pd3dDevice->CreateTexture2D(&tx.des, NULL, &tx.get);
#endif
	}

	void Device::CreateDepthStencilView(DepthStencil& ds)
	{
#ifdef directX
		g_pd3dDevice->CreateDepthStencilView(ds.textur.get, &ds.des, &ds.view);
#endif
	}

	
#ifdef directX
	HRESULT Device::CreateVertexShader(ID3DBlob* pPSBlob, ID3D11VertexShader** vertexshader)
	{
		pVSBlob = pPSBlob;
		return g_pd3dDevice->CreateVertexShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, vertexshader);
	}
#endif
	/*HRESULT Device::CreateInputLayout()
	{
		g_pVertexLayout = NULL;
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);
		HRESULT r = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
			pVSBlob->GetBufferSize(), &g_pVertexLayout);
		pVSBlob->Release();
		return r;
	}//*/
#ifdef directX
	HRESULT Device::CreatePixelShader(ID3DBlob* pPSBlob, ID3D11PixelShader** pPixelShader)
	{

		HRESULT hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, pPixelShader);;
		pPSBlob->Release();
		return hr;

	}
#endif
	

	

	void Device::CreateShaderResourceViewFromFile(LPCSTR file)
	{
#ifdef directX
		D3DX11CreateShaderResourceViewFromFile(g_pd3dDevice, file, NULL, NULL, &g_pTextureRV, NULL);
#endif
	}

	void Device::CreateShaderResourceView(RenderTargetView& rtv, D3D11_SHADER_RESOURCE_VIEW_DESC des)
	{
#ifdef directX
		g_pd3dDevice->CreateShaderResourceView(rtv.textur.get, &des, &rtv.srv);
#endif
	}

	

	void Device::CreateBuffer(D3D11_BUFFER_DESC& bd, D3D11_SUBRESOURCE_DATA& InitData, Buffer& b)
	{

#ifdef directX
		 g_pd3dDevice->CreateBuffer(&bd, &InitData, &b.buf);
#endif // directX
		
	}

	void Device::CreateBuffer(D3D11_BUFFER_DESC& bd, Buffer& b)
	{
#ifdef directX
		g_pd3dDevice->CreateBuffer(&bd, NULL, &b.buf);
#endif // directX

		
	}

	
	Device::~Device()
	{
		g_pd3dDevice->Release();
	}

}

