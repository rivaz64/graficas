#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include"Device.h"
#include<vector>
#include"mesh.h"
#include"Textura.h"
using std::vector;
class camera;
namespace GraphicsModule {
	class DeviceContext
	{
	public:
		Device* dev;

		ID3D11DeviceContext* g_pImmediateContext;
		float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
		XMFLOAT4 g_vMeshColor = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
		void OMSetRenderTargets();
		void RSSetViewports(UINT width, UINT height);
		void IASetInputLayout();
		void IASetVertexBuffers(Buffer* b);
		void IASetIndexBuffer(Buffer* b);
		void UpdateSubresource(camera* cam);
		void UpdateView(camera* cam);
		void resizewindow(camera* cam, HWND& g_hWnd);
		void render(std::vector<float*>& instanses);
		void PSSetShaderResources(Textura&t);
	};
}


