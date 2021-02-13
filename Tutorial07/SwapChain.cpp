#include "SwapChain.h"

HRESULT SwapChain::GetBuffer()
{
	return g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
}
