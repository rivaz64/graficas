#include "SwapChain.h"
#include "manager.h"
namespace GraphicsModule {
	

	

	void SwapChain::rezise(LPARAM lParam,RenderTargetView& rtv)
	{
		rtv.release();
#ifdef directX
		g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam),(DXGI_FORMAT)FORMAT::UNKNOWN, 0);
#endif
		getmanager()->createrendertarget(rtv);
	}

	void SwapChain::GetBuffer(Textura& t)
	{
#ifdef directX
		g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&t.get);
#endif
	}

	void SwapChain::Present()
	{
#ifdef directX
		g_pSwapChain->Present(0, 0);
#endif
	}

}

