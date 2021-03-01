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
	viewport vp;
	void createdesctriptor(HWND g_hWnd, UINT width, UINT height);
    void rezise(LPARAM lparam);
	void Present();
};

