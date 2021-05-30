#include "renderer.h"

namespace GraphicsModule {
	void Renderer::init(FORMAT f, FORMAT d,bool b)
	{
		tex.describe(f, BIND_FLAG::RENDER_TARGET);
		getmanager()->getDevice()->CreateTexture2D(tex);
		if (b) {
			rtv.Format = f;
			rtv.ViewDimension = DIMENSION::TEXTURE2D;
			rtv.textur = tex;
			getmanager()->getDevice()->CreateRenderTargetView(rtv, false);
			getmanager()->getDevice()->CreateShaderResourceView(rtv);
		}
		else {
			//Textura pBackBuffer;
			getmanager()->getSwapchain()->GetBuffer(tex);
			rtv.textur = tex;
			getmanager()->getDevice()->CreateRenderTargetView(rtv, false);

		}
		getmanager()->getDevice()->CreateShaderResourceView(rtv);
		depth.textur.describe(d, BIND_FLAG::DEPTH_STENCIL);
		depth.textur.des.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::DEPTH_STENCIL;
		getmanager()->getDevice()->CreateTexture2D(depth.textur);
		depth.describeview();
		
		HRESULT hr;
		hr = getmanager()->getDevice()->CreateDepthStencilView(depth);
		if (FAILED(hr)) {
			int x = 1;
		}
		vp.Width = (FLOAT)getmanager()->width;
		vp.Height = (FLOAT)getmanager()->height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
	}
	void Renderer::setTargets()
	{
		getmanager()->getConext()->OMSetRenderTargets(rtv, depth);
		getmanager()->RSSetViewports(vp);
	}
	void Renderer::clearTargets()
	{
		getmanager()->getConext()->ClearRenderTargetView(rtv);
		getmanager()->getConext()->ClearDepthStencilView(depth);
	}
	void Renderer::render()
	{
	}
}

