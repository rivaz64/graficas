#pragma once
#include"mesh.h"
#include"Textura.h"
#include"model.h"
#include"vector3.h"
#include "RenderTargetView.h"
namespace GraphicsModule {
	class objeto {
	public:
		//mesh* m;
		model* mod;
		Textura* tx=NULL;
		vector3 posi;
		XMFLOAT4 color;
		void setTexture(RenderTargetView rtv);
	};
}
