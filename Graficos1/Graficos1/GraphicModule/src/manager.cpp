#include "manager.h"
#include"flags.h"
namespace GraphicsModule {
	void manager::create(HWND g_hWnd) {
		RECT rc;
		g_hWndM = g_hWnd;
		GetClientRect(g_hWnd, &rc);
		width = rc.right - rc.left;
		height = rc.bottom - rc.top;
	}

	void manager::descrivesch()
	{
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
	}

	HRESULT manager::init(DRIVER_TYPE v_driverType, UINT createDeviceFlags, FEATURE_LEVEL* featureLevels, UINT numFeatureLevels, FEATURE_LEVEL g_featureLevel)
	{
		return D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)v_driverType, NULL, createDeviceFlags, (D3D_FEATURE_LEVEL*)featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &eswap.g_pSwapChain, &dev.g_pd3dDevice, (D3D_FEATURE_LEVEL*)(&g_featureLevel), &devcon.g_pImmediateContext);
	}
	void manager::createrendertarget(RenderTargetView& rtv)
	{
		Textura pBackBuffer;
		eswap.g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer.get);
		
		dev.g_pd3dDevice->CreateRenderTargetView(pBackBuffer.get, NULL, &rtv.get);
		pBackBuffer.get->Release();
	}

	void manager::CreateTexture2D(Textura& tx)
	{
		dev.g_pd3dDevice->CreateTexture2D(&tx.des, NULL, &tx.get);
	}

	void manager::CreateDepthStencilView(DepthStencil& ds)
	{
		dev.g_pd3dDevice->CreateDepthStencilView(ds.textur.get, &ds.des, &ds.view);
	}

	void manager::OMSetRenderTargets(RenderTargetView& rtv, DepthStencil& ds)
	{
		devcon.g_pImmediateContext->OMSetRenderTargets(1, &rtv.get, ds.view);
	}

	void manager::RSSetViewports(Viewport& vp)
	{
		
		v.Width = vp.Width;
		v.Height = vp.Height;
		v.MinDepth = vp.MinDepth;
		v.MaxDepth = vp.MaxDepth;
		v.TopLeftX = vp.TopLeftX;
		v.TopLeftY = vp.TopLeftY;
		devcon.g_pImmediateContext->RSSetViewports(1, &v);
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
