#include "DeviceContext.h"

void DeviceContext::OMSetRenderTargets(Device* v_device)
{
	g_pImmediateContext->OMSetRenderTargets(1,v_device->g_pRenderTargetView , v_device->DepthStencilView);
}

void DeviceContext::RSSetViewports(UINT width, UINT height)
{
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	//g_pImmediateContext->RSSetViewports(1, &vp);
}
