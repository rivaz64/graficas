#include "renderer.h"

namespace GraphicsModule {
	void Renderer::init(FORMAT f, FORMAT d)
	{
		tex.describe(f, BIND_FLAG::RENDER_TARGET);
		getmanager()->getDevice()->CreateTexture2D(tex);
		rtv.Format = f;
		rtv.ViewDimension = DIMENSION::TEXTURE2D;
		rtv.textur = tex;
		getmanager()->getDevice()->CreateRenderTargetView(rtv, true);
		getmanager()->getDevice()->CreateShaderResourceView(rtv);
		depth.textur.describe(d, BIND_FLAG::DEPTH_STENCIL);
		getmanager()->getDevice()->CreateTexture2D(depth.textur);
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
}

