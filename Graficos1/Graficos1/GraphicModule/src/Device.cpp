#include "Device.h"
#include"DeviceContext.h"
#include "SwapChain.h"
#include"test.h"
/*D3D_DRIVER_TYPE driverTypes[] =
{
	D3D_DRIVER_TYPE_HARDWARE,
	D3D_DRIVER_TYPE_WARP,
	D3D_DRIVER_TYPE_REFERENCE,
};
UINT numDriverTypes = ARRAYSIZE(driverTypes);

D3D_FEATURE_LEVEL featureLevels[] =
{
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0,
};
UINT numFeatureLevels = ARRAYSIZE(featureLevels);*/


HRESULT Device::create(HWND g_hWnd )
{
	RECT rc;
	g_hWndM = g_hWnd;
	GetClientRect(g_hWnd, &rc);
	 width = rc.right - rc.left;
	 height = rc.bottom - rc.top;
	 return S_OK;
}
HRESULT Device::CreateRenderTargetView(ID3D11Texture2D* textura)
{
	return g_pd3dDevice->CreateRenderTargetView(textura, NULL, &g_pRenderTargetView);
}

HRESULT Device::CreateTexture2D()
{
	return S_OK;
	/*ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	return g_pd3dDevice->CreateTexture2D(&descDepth, NULL, &depstencil.get);*/
}

HRESULT Device::CreateDepthStencilView()
{

	/*D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	DepthStencilView = NULL;
	return g_pd3dDevice->CreateDepthStencilView(depstencil.get, &descDSV, &DepthStencilView);*/
	return S_OK;
}

HRESULT Device::CreateVertexShader(ID3DBlob* pPSBlob)
{
	
	/*hr = */
	/*if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}*/
	pVSBlob = pPSBlob;
	return g_pd3dDevice->CreateVertexShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &vertexshader);
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

HRESULT Device::CreatePixelShader(ID3DBlob* pPSBlob)
{

	HRESULT hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);;
	pPSBlob->Release();
	return hr;
}

HRESULT Device::CreateBuffers()
{
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(GraphicsModule::CBNeverChanges);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	g_pd3dDevice->CreateBuffer(&bd, NULL, &neverChangesB.buf);
	bd.ByteWidth = sizeof(GraphicsModule::CBChangeOnResize);
	g_pd3dDevice->CreateBuffer(&bd, NULL, &changesOnReziseB.buf);
	bd.ByteWidth = sizeof(GraphicsModule::CBChangesEveryFrame);
	return g_pd3dDevice->CreateBuffer(&bd, NULL, &changeveryFrameB.buf);
}

void Device::setmesh(mesh* m)
{
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
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

Device::~Device()
{
	/*delete g_pd3dDevice;
	delete g_pRenderTargetView;
	delete (*deptstencil);
	delete deptstencil;*/
}
