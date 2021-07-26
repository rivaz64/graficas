#include "renderer.h"
#include "manager.h"
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
namespace GraphicsModule {
#ifdef openGL
	GLenum *Renderer::DrawBuffers = new GLenum[10]{ 
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3,
		GL_COLOR_ATTACHMENT4,
		GL_COLOR_ATTACHMENT5,
		GL_COLOR_ATTACHMENT6,
		GL_COLOR_ATTACHMENT7,
		GL_COLOR_ATTACHMENT8,
		GL_COLOR_ATTACHMENT9,
	};
#endif
	void Renderer::init(FORMAT f, FORMAT d,bool b,int n, SRV_DIMENSION dsrv, CULING cul)
	{
		size = n;
#ifdef openGL
		GLenum* Draws =new GLenum[n];
		glGenFramebuffers(1, &FramebufferName);
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
#endif

		for (int i = 0; i < n; i++) {
			tex.push_back(Textura());
			tex[i].describe(f, BIND_FLAG::RENDER_TARGET);
#ifdef directX
			tex[i].des.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
#endif
			tex[i].init();
#ifdef openGL
			glFramebufferTexture(GL_FRAMEBUFFER, DrawBuffers[i], getmanager()->screen->mod->modelo[0]->material[i]->srv.get, 0);
			Draws[i] = DrawBuffers[i];
#endif
		}

#ifdef openGL
		glDrawBuffers(n, Draws);
#endif

		depth.textur.describe(d, BIND_FLAG::DEPTH_STENCIL);

#ifdef directX
		depth.textur.des.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::DEPTH_STENCIL;
#endif

		depth.textur.init();
		depth.describeview();

		getmanager()->getDevice()->CreateDepthStencilView(depth);






		if (b) {
			rtv.Format = f;
			rtv.ViewDimension = DIMENSION::TEXTURE2D;
			rtv.textur = tex;
			rtv.srv.resize(n);

			getmanager()->getDevice()->CreateRenderTargetView(rtv, true,n);
			//getmanager()->getDevice()->CreateShaderResourceView(rtv);
		}
#ifdef directX
		else {
			//Textura pBackBuffer;
			getmanager()->getSwapchain()->GetBuffer(tex[0]);
			rtv.textur =tex;
			getmanager()->getDevice()->CreateRenderTargetView(rtv, false,n);

		}
		getmanager()->getDevice()->CreateShaderResourceView(rtv,n,dsrv);
		//aka iva el dep
		/*if (FAILED(hr)) {
			int x = 1;
		}*/
		vp.Width = (FLOAT)getmanager()->width;
		vp.Height = (FLOAT)getmanager()->height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		ras.create(cul);
#endif
#ifdef openGL
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			return ;
#endif
#ifdef directX
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&samsta.desc, sizeof(samsta.desc));
		samsta.desc.Filter = (D3D11_FILTER)FILTER::COMPARISON_MIN_MAG_MIP_LINEAR;
		samsta.desc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
		samsta.desc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
		samsta.desc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
		samsta.desc.ComparisonFunc = (D3D11_COMPARISON_FUNC)COMPARISON_FUNC::NEVER;
		samsta.desc.MipLODBias = 0;
		samsta.desc.MinLOD = 0;
		samsta.desc.MaxLOD = D3D11_FLOAT32_MAX;
		getmanager()->getDevice()->CreateSamplerState(samsta);
#endif
/*#ifdef openGL
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
#endif*/

	}
	void Renderer::setTargets()
	{
#if openGL
		//glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
#endif
#ifdef directX
		getmanager()->getConext()->get()->OMSetRenderTargets(size, rtv.get.data(), depth.view);
		getmanager()->getConext()->get()->PSSetSamplers(0,1,&samsta.get);
#endif
		
		getmanager()->RSSetViewports(vp);
		ras.setear();
		getmanager()->actualRen = this;
	}
	void Renderer::clearTargets(bool clearDepth)
	{
#ifdef openGL
		glClearColor(.0f, .0f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
		
		getmanager()->getConext()->ClearDepthStencilView(depth);
		if(clearDepth)
			getmanager()->getConext()->ClearRenderTargetView(rtv, size);
	}
	void Renderer::render()
	{
#ifdef openGL
		//glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0, 0, 1024, 768);
#endif
	}
}

