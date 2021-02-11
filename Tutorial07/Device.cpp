#include "Device.h"
HRESULT CompileShaderFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}
HRESULT Device::CreateRenderTargetView(ID3D11Texture2D* textura, ID3D11RenderTargetView** targetView)
{
	return g_pd3dDevice->CreateRenderTargetView(textura, NULL, targetView);
}

HRESULT Device::CreateTexture2D(UINT width, UINT height, ID3D11Texture2D** DepthStencil)
{
	ZeroMemory(&descDepth, sizeof(descDepth));
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
	deptstencil = DepthStencil;
	return g_pd3dDevice->CreateTexture2D(&descDepth, NULL, deptstencil);
}

HRESULT Device::CreateDepthStencilView()
{

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	DepthStencilView = NULL;
	return g_pd3dDevice->CreateDepthStencilView(*deptstencil, &descDSV, &DepthStencilView);
}

HRESULT Device::CreateVertexShader(wchar_t* file, const char* vs, const char* vsv, ID3D11VertexShader** vertexshader)
{
	ID3DBlob* pVSBlob = NULL;
	/*hr = */CompileShaderFile(file, vs, vsv, &pVSBlob);
	/*if (FAILED(hr))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}*/
	return g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, vertexshader);
}

Device::~Device()
{
	/*delete g_pd3dDevice;
	delete g_pRenderTargetView;
	delete (*deptstencil);
	delete deptstencil;*/
}
