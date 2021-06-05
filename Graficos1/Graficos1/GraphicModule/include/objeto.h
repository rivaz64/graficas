#pragma once
#include"mesh.h"
#include"Textura.h"
#include"model.h"
#include"vector3.h"
#include "RenderTargetView.h"

namespace GraphicsModule {
	class objeto {
	public:
		std::vector<Textura*> material;
		//mesh* m;
		model* mod;
		int shaderid = 0;
		//Textura* tx=NULL;
		float posi[3] = { 0,0,0 };
		float size[3] = { 1,1,1 };
		float rot[3] = { 0,0,0 };
		//float color[4];
		void setTexture(RenderTargetView rtv);
		void setTexture(unsigned int t);
	};
}
