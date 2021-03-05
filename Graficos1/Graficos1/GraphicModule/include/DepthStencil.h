#pragma once
#include"Textura.h"
namespace GraphicsModule {
	class DepthStencil
	{
		
	public:
#ifdef directX
		D3D11_DEPTH_STENCIL_VIEW_DESC des;
		ID3D11DepthStencilView* view;
#endif
		Textura textur;
		void descrivetextur();
		void describeview();
	};
}


