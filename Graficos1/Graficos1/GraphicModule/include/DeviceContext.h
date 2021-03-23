#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include"Device.h"
#include<vector>
#include"mesh.h"
#include"Textura.h"
#include"RenderTargetView.h"
#include"DepthStencil.h"
#include"InputLayout.h"
#include"flags.h"
#include"PixelShader.h"
using std::vector;
class camera;
namespace GraphicsModule {
	class DeviceContext
	{
#ifdef directX
		ID3D11DeviceContext* g_pImmediateContext;
#endif
	public:
#ifdef directX
		ID3D11DeviceContext* get() {
			return g_pImmediateContext;
		}
#else
		void get() {}
#endif
		float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
		XMFLOAT4 g_vMeshColor = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
		void RSSetViewports(Viewport& vp);
		void IASetVertexBuffers(Buffer* b);
		void IASetIndexBuffer(Buffer* b);
		void UpdateView(camera* cam);
		void resizewindow(camera* cam, HWND& g_hWnd, RenderTargetView &rtv, Buffer& chor);
		void IASetPrimitiveTopology(PRIMITIVE_TOPOLOGY pt);
		void ClearRenderTargetView(RenderTargetView& rtv);
		void PSSetShaderResources(Textura*t);
		void OMSetRenderTargets(RenderTargetView& r, DepthStencil& d);
		void ClearDepthStencilView(DepthStencil& d);
		void UpdateSubresource(Buffer& b, const void * c);
		void VSSetShader(VertexShader& vs);
		void PSSetShader(PixelShader& ps);
		void IASetInputLayout(InputLayout& il);

		void draw(int n);
		friend class manager;
		~DeviceContext();
	};
}


