#pragma once
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#include"Device.h"

#include"mesh.h"
#include"Textura.h"
#include"RenderTargetView.h"
#include"DepthStencil.h"
#include"InputLayout.h"
#include"flags.h"
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
		float g_vMeshColor[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
		void IASetVertexBuffers(Buffer* b);
		void IASetIndexBuffer(Buffer* b);

		void VSSetConstantBuffers(int i, Buffer* b);
		void VSSetConstantBuffers(int i, Buffer* b,int size);
		void PSSetConstantBuffers(int i, Buffer* b);

		void UpdateView(camera* cam);
		void resizewindow(camera* cam, HWND& g_hWnd, RenderTargetView &rtv, Buffer& chor);
		void IASetPrimitiveTopology(PRIMITIVE_TOPOLOGY pt);
		void ClearRenderTargetView(RenderTargetView& rtv,int n);
		void PSSetShaderResources(Textura*t,int cual);
		void OMSetRenderTargets(RenderTargetView& r, DepthStencil& d);
		void ClearDepthStencilView(DepthStencil& d);
		void UpdateSubresource(Buffer& b, 
#ifdef directX
			const
#endif
			void * c);
		void VSSetShader(VertexShader& vs);
		void IASetInputLayout(InputLayout& il);

		void draw(int n, PRIMITIVE_TOPOLOGY pt);
		friend class manager;
		~DeviceContext();
	};
}


