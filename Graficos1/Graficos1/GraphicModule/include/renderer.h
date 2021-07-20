#pragma once
#include "Textura.h"
#include"DepthStencil.h"
#include"viewport.h"
#include "chader.h"
#include <vector>
#include "Rasterizer.h"
#include "SamplerState.h"
#include "..\include\RenderTargetView.h"
namespace GraphicsModule {
	class Renderer
	{
		int size;
	public:

		SamplerState samsta;
		std::vector<Textura> tex;
		RenderTargetView rtv;
		DepthStencil depth;
		Viewport vp;
		chader* shad;
		Rasterizer ras;
#ifdef openGL
		static GLenum* DrawBuffers;
		GLuint renderedTexture;
		GLuint FramebufferName = 0;
#endif
		void init(FORMAT f,FORMAT d,bool b,int n, SRV_DIMENSION dsrv,CULING cul);
		void setTargets();
		void clearTargets(bool clearDepth);
		void render();
	};
}


