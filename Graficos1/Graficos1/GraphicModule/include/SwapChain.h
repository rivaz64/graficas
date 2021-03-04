#pragma once
#include"Device.h"
namespace GraphicsModule {
	class SwapChain
	{
#ifdef directX
		IDXGISwapChain* g_pSwapChain = NULL;
#endif
	public:
#ifdef directX
		IDXGISwapChain* get() { return g_pSwapChain; }
#else
		void get() {}
#endif
		DXGI_SWAP_CHAIN_DESC sd;
		ID3D11RenderTargetView* g_pRenderTargetView;
		void rezise(LPARAM lparam, RenderTargetView& rtv);
		void Present();
		friend class manager;
	};
}


