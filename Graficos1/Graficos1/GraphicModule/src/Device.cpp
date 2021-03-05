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
	HRESULT Device::CreateRenderTargetView(Textura& textura,RenderTargetView& rtv)
	{
		return g_pd3dDevice->CreateRenderTargetView(textura.get, NULL, &rtv.get);
	}

	void Device::CreateTexture2D(Textura& tx)
	{
		g_pd3dDevice->CreateTexture2D(&tx.des, NULL, &tx.get);
	}

	void Device::CreateDepthStencilView(DepthStencil& ds)
	{
		g_pd3dDevice->CreateDepthStencilView(ds.textur.get, &ds.des, &ds.view);
	}

	

	HRESULT Device::CreateVertexShader(ID3DBlob* pPSBlob, ID3D11VertexShader** vertexshader)
	{
		pVSBlob = pPSBlob;
		return g_pd3dDevice->CreateVertexShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, vertexshader);
	}

	HRESULT Device::CreateInputLayout()
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
	}

	HRESULT Device::CreatePixelShader(ID3DBlob* pPSBlob, ID3D11PixelShader** pPixelShader)
	{

		HRESULT hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, pPixelShader);;
		pPSBlob->Release();
		return hr;
	}

	

	void Device::setmesh(mesh* m)
	{
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = (D3D11_USAGE)USAGE::DEFAULT;
		bd.ByteWidth = sizeof(mesh::vertex) * 24;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = m->getvertex();
		g_pd3dDevice->CreateBuffer(&bd, &InitData, &vertexB.buf);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * 36;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = m->getindices();
		g_pd3dDevice->CreateBuffer(&bd, &InitData, &indexB.buf);
	}

	void Device::CreateShaderResourceViewFromFile(LPCSTR file)
	{
		D3DX11CreateShaderResourceViewFromFile(g_pd3dDevice, file, NULL, NULL, &g_pTextureRV, NULL);

	}

	void Device::CreateShaderResourceView(RenderTargetView& rtv, D3D11_SHADER_RESOURCE_VIEW_DESC des)
	{
		g_pd3dDevice->CreateShaderResourceView(rtv.textur.get, &des, &rtv.srv);
	}

	HRESULT Device::CreateSamplerState()
	{

		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		return g_pd3dDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear);;
	}

	HRESULT Device::CreateBuffer(D3D11_BUFFER_DESC& bd, D3D11_SUBRESOURCE_DATA& InitData, Buffer& b)
	{
		return g_pd3dDevice->CreateBuffer(&bd, &InitData, &b.buf);
	}

	void Device::CreateBuffer(D3D11_BUFFER_DESC& bd, Buffer& b)
	{
		g_pd3dDevice->CreateBuffer(&bd, NULL, &b.buf);
	}

	

	Device::~Device()
	{
		/*delete g_pd3dDevice;
		delete g_pRenderTargetView;
		delete (*deptstencil);
		delete deptstencil;*/
	}

}

