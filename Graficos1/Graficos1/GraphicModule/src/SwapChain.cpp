#include "SwapChain.h"

HRESULT SwapChain::GetBuffer()
{
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	HRESULT hr=dev->CreateRenderTargetView(pBackBuffer);
	pBackBuffer->Release();
	return hr;
}

void SwapChain::rezise(LPARAM lParam)
{
    dev->vp.release();
    g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
    GetBuffer();
}

void SwapChain::Present()
{
	g_pSwapChain->Present(0, 0);
}

