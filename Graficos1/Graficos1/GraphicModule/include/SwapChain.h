#pragma once
#include"Device.h"
class SwapChain
{
public:
	Device* dev;
	IDXGISwapChain* g_pSwapChain = NULL;
	ID3D11Texture2D* pBackBuffer = NULL;
	HRESULT GetBuffer();
    void rezise(LPARAM lparam);
	void Present();
};

