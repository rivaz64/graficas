#pragma once
#include "Textura.h"
#include "manager.h"
#include"DepthStencil.h"
#include"viewport.h"
#include "chader.h"
#include <vector>
namespace GraphicsModule {
	class Renderer
	{
		int size;
	public:
		std::vector<Textura> tex;
		RenderTargetView rtv;
		DepthStencil depth;
		Viewport vp;
		chader* shad;
		ID3D11RasterizerState* g_Rasterizer = NULL;
#ifdef openGL
		GLuint renderedTexture;
		GLuint FramebufferName = 0;
#endif
		void init(FORMAT f,FORMAT d,bool b,int n, SRV_DIMENSION dsrv);
		void setTargets();
		void clearTargets();
		void render();
	};
}


