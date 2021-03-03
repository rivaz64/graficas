#pragma once
#include"mesh.h"
#include"Textura.h"
#include"vector3.h"
namespace GraphicsModule {
	class objeto {
	public:
		mesh* m;
		Textura* tx;
		vector3 posi;
		XMFLOAT4 color;
	};
}
