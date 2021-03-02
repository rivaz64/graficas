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
		sd.BufferDesc.Width = dev->width;
		sd.BufferDesc.Height = dev->height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = dev->g_hWndM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
	}

	HRESULT manager::init(DRIVER_TYPE v_driverType,UINT createDeviceFlags,UINT featureLevels,UINT numFeatureLevels,FEATURE_LEVEL g_featureLevel)
	{
		return D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)v_driverType, NULL, createDeviceFlags, (D3D_FEATURE_LEVEL*)featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, (D3D_FEATURE_LEVEL*)(&g_featureLevel), &g_pImmediateContext);
	}
}

