#include "SwapChain.h"
#include "manager.h"
namespace GraphicsModule {
	

	

	void SwapChain::rezise(LPARAM lParam,RenderTargetView& rtv)
	{
		rtv.release();
		g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam),(DXGI_FORMAT)FORMAT::UNKNOWN, 0);
		getmanager()->createrendertarget(rtv);
	}

	void SwapChain::GetBuffer(Textura& t)
	{
		g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&t.get);
	}

	void SwapChain::Present()
	{
		g_pSwapChain->Present(0, 0);
	}

}

