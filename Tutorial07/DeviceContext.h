#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include"Device.h"
class DeviceContext
{
public:
	Device* dev;
	ID3D11DeviceContext* g_pImmediateContext;
	void OMSetRenderTargets(Device* v_device);
	void RSSetViewports(UINT width, UINT height);
	void IASetInputLayout();
	void IASetVertexBuffers();
	void IASetIndexBuffer();
};

