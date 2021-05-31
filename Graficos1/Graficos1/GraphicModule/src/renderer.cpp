#include "renderer.h"

namespace GraphicsModule {
	void Renderer::init(FORMAT f, FORMAT d,bool b)
	{
#ifdef directX
		tex.describe(f, BIND_FLAG::RENDER_TARGET);
		getmanager()->getDevice()->CreateTexture2D(tex);
		if (b) {
			rtv.Format = f;
			rtv.ViewDimension = DIMENSION::TEXTURE2D;
			rtv.textur = tex;
			getmanager()->getDevice()->CreateRenderTargetView(rtv, true);
			//getmanager()->getDevice()->CreateShaderResourceView(rtv);
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
		
		//HRESULT hr;
		getmanager()->getDevice()->CreateDepthStencilView(depth);
		/*if (FAILED(hr)) {
			int x = 1;
		}*/
		vp.Width = (FLOAT)getmanager()->width;
		vp.Height = (FLOAT)getmanager()->height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
#endif
#ifdef openGL
		if (b) {
			glGenFramebuffers(1, &FramebufferName);
			glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
			// The texture we're going to render to
			
			glGenTextures(1, &renderedTexture);

			// "Bind" the newly created texture : all future texture functions will modify this texture
			glBindTexture(GL_TEXTURE_2D, renderedTexture);

			// Give an empty image to OpenGL ( the last "0" )
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, getmanager()->width, getmanager()->height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

			// Poor filtering. Needed !
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			GLuint depthrenderbuffer;
			glGenRenderbuffers(1, &depthrenderbuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, getmanager()->width, getmanager()->height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

			// Set the list of draw buffers.
			GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, DrawBuffers);
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				int xyz = 1;
		}
#endif

	}
	void Renderer::setTargets()
	{
#if openGL
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
#endif
		getmanager()->getConext()->OMSetRenderTargets(rtv, depth);
		getmanager()->RSSetViewports(vp);
	}
	void Renderer::clearTargets()
	{
#ifdef openGL
		glClearColor(.0f, .0f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
		getmanager()->getConext()->ClearRenderTargetView(rtv);
		getmanager()->getConext()->ClearDepthStencilView(depth);
	}
	void Renderer::render()
	{
#ifdef openGL
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0, 0, 1024, 768);
#endif
	}
}

