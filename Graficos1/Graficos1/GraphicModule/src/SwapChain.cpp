#include "SwapChain.h"
#include "manager.h"
namespace GraphicsModule {
	HRESULT SwapChain::GetBuffer()
	{
		g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		dev->CreateRenderTargetView(pBackBuffer);
		pBackBuffer->Release();
		return S_OK;
	}

	void SwapChain::createdesctriptor()
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

	void SwapChain::rezise(LPARAM lParam,RenderTargetView& rtv)
	{
		rtv.release();
		g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam),(DXGI_FORMAT)FORMAT::UNKNOWN, 0);
		getmanager()->createrendertarget(rtv);
	}

	void SwapChain::Present()
	{
		g_pSwapChain->Present(0, 0);
	}

}

