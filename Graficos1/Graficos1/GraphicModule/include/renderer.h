#pragma once
#include "Textura.h"
#include "manager.h"
#include"DepthStencil.h"
#include"viewport.h"
#include "chader.h"
namespace GraphicsModule {
	class Renderer
	{
		
	public:
		Textura tex;
		RenderTargetView rtv;
		DepthStencil depth;
		Viewport vp;
		chader* shad;
		void init(FORMAT f,FORMAT d,bool b);
		void setTargets();
		void clearTargets();
		void render();
	};
}


