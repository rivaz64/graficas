#include "SwapChain.h"
#include "manager.h"
namespace GraphicsModule {
	

	

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

