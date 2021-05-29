#pragma once
#include "Textura.h"
#include "manager.h"
#include"DepthStencil.h"
#include"viewport.h"
namespace GraphicsModule {
	class Renderer
	{
		Textura tex;
		RenderTargetView rtv;
		DepthStencil depth;
		Viewport vp;
	public:
		void init(FORMAT f,FORMAT d);
		void setTargets();
		void clearTargets();
	};
}


