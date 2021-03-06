#pragma once
#include"Device.h"
#include"viewport.h"
namespace GraphicsModule {
	class SwapChain
	{
#ifdef directX
		IDXGISwapChain* g_pSwapChain = NULL;
		DXGI_SWAP_CHAIN_DESC sd;
#endif
	public:
#ifdef directX
		IDXGISwapChain* get() { return g_pSwapChain; }
#else
		void get() {}
#endif
		
		ID3D11RenderTargetView* g_pRenderTargetView;
		void rezise(LPARAM lparam, RenderTargetView& rtv,bool main);
		void GetBuffer(Textura&t);
		void Present();
		friend class manager;
	};
}


