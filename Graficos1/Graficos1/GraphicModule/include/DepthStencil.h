#pragma once
#include"Textura.h"
namespace GraphicsModule {
	class DepthStencil
	{
	public:
		Textura textur;
		D3D11_DEPTH_STENCIL_VIEW_DESC des;
		ID3D11DepthStencilView* view;
		void descrivetextur();
		void describeview();
	};
}


