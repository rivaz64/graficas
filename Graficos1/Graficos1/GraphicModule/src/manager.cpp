#include "manager.h"
#include"flags.h"
#include"test.h"
namespace GraphicsModule {
#ifdef directX
	HRESULT manager::CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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
		hr = D3DX11CompileFromFileA(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
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
#endif
	void manager::create(HWND g_hWnd) {
		RECT rc;
		g_hWndM = g_hWnd;
		GetClientRect(g_hWnd, &rc);
		width = rc.right - rc.left;
		height = rc.bottom - rc.top;
	}

	void manager::descrivesch()
	{
#ifdef directX
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = g_hWndM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
#endif
	}

	HRESULT manager::init(DRIVER_TYPE v_driverType, UINT createDeviceFlags, FEATURE_LEVEL* featureLevels, UINT numFeatureLevels, FEATURE_LEVEL g_featureLevel)
	{
#ifdef directX
		return D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)v_driverType, NULL, createDeviceFlags, (D3D_FEATURE_LEVEL*)featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &eswap.g_pSwapChain, &dev.g_pd3dDevice, (D3D_FEATURE_LEVEL*)(&g_featureLevel), &devcon.g_pImmediateContext);
#endif // directX
		return S_FALSE;

	}
	void manager::createrendertarget(RenderTargetView& rtv)
	{
		Textura pBackBuffer;
		eswap.GetBuffer(pBackBuffer);
		rtv.textur = pBackBuffer;
		dev.CreateRenderTargetView(rtv);
		pBackBuffer.release();
	}





	void manager::RSSetViewports(Viewport& vp)
	{
#ifdef directX
		v.Width = vp.Width;
		v.Height = vp.Height;
		v.MinDepth = vp.MinDepth;
		v.MaxDepth = vp.MaxDepth;
		v.TopLeftX = vp.TopLeftX;
		v.TopLeftY = vp.TopLeftY;

		devcon.g_pImmediateContext->RSSetViewports(1, &v);
#endif // directX


	}



	void manager::draw(objeto &o, Buffer& changeveryFrameB)
	{
#ifdef directX
		for (mesh* mo : (o.mod->modelo)) {

			devcon.IASetVertexBuffers(mo->getvertex());
			devcon.IASetIndexBuffer(mo->getindices());
			if (o.tx != NULL)
				devcon.PSSetShaderResources(o.tx);
			XMMATRIX g_World;
			CBChangesEveryFrame cb;
			g_World = XMMatrixTranslation(o.posi.x, o.posi.y, o.posi.z);

			cb.mWorld = XMMatrixTranspose(g_World);

			//cb.vMeshColor = o.color;
			devcon.UpdateSubresource(changeveryFrameB, &cb);

			devcon.draw(mo->indexnum);
		}
#endif
	}

	void manager::setrenderfortextur(RenderTargetView& rtv)
	{
#ifdef  directX

		rtv.release();
		rtv.textur.release();
		
		rtv.textur.describe(FORMAT::R8G8B8A8_UNORM, BIND_FLAG::RENDER_TARGET);
		dev.CreateTexture2D(rtv.textur);
		
		rtv.Format = FORMAT::R8G8B8A8_UNORM;
		rtv.ViewDimension = DIMENSION::TEXTURE2DARRAY;
		rtv.MostDetailedMip = 0;
		rtv.MipLevels = 1;
		dev.CreateShaderResourceView(rtv);
		dev.CreateRenderTargetView(rtv);
#endif
	}

	HRESULT manager::compileVS(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,  VertexShader& vs,InputLayout& il)
	{
#ifdef directX
		ID3DBlob* pVSBlob = NULL;
		HRESULT hr = CompileShaderFromFile(szFileName, szEntryPoint, szShaderModel, &pVSBlob);
		if (FAILED(hr))
		{
			MessageBox(NULL,
				"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
			return hr;
		}
		dev.createVSwithInput(vs, il, pVSBlob);
		pVSBlob->Release();
		return hr;
#endif
		return S_OK;
	}

	HRESULT manager::compilePX(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, PixelShader& px)
	{
#ifdef directX
		ID3DBlob* pPSBlob = NULL;
		HRESULT hr = CompileShaderFromFile(szFileName, szEntryPoint, szShaderModel, &pPSBlob);
		if (FAILED(hr))
		{
			MessageBox(NULL,
				"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
			return hr;
		}

		// Create the pixel shader
		ID3D11PixelShader* g_pPixelShader;
		hr = dev.CreatePixelShader(pPSBlob, &g_pPixelShader);
		px.g_pPixelShader = g_pPixelShader;
		pPSBlob->Release();
#endif
		return S_OK;
	}
	
	manager* getmanager()
	{
		static manager* man;
		if (man == NULL) {
			man = new manager;
		}
		return man;
	}

}

