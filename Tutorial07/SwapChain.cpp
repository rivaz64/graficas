#include "SwapChain.h"

HRESULT SwapChain::GetBuffer()
{
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	HRESULT hr=dev->CreateRenderTargetView(pBackBuffer);
	pBackBuffer->Release();
	return hr;
}

void SwapChain::Present()
{
	g_pSwapChain->Present(0, 0);
}

