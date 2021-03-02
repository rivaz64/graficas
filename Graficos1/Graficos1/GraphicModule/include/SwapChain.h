#pragma once
#include"Device.h"

class SwapChain
{
public:
	Device* dev;
	IDXGISwapChain* g_pSwapChain = NULL;
	ID3D11Texture2D* pBackBuffer = NULL;
	HRESULT GetBuffer();
	DXGI_SWAP_CHAIN_DESC sd;
	ID3D11RenderTargetView* g_pRenderTargetView;
	void createdesctriptor();
    void rezise(LPARAM lparam);
	void Present();
};

