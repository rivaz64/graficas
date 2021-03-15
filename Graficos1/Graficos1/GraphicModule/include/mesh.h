#pragma once
#include <initializer_list>
#include"Buffer.h"
namespace GraphicsModule {
	class mesh
	{
		int indexnum;
	public:
		struct vertex {
			float posi[3];
			float uv[2];
			float normal[3];
		};
		vertex* points;
		short* indices;
		Buffer vertexB;
		Buffer indexB;
		Buffer* getindices();
		void setindices(std::initializer_list<short> i);
		Buffer* getvertex();
		void setvertex(std::initializer_list<vertex> i);
		void init(int nv, int ni);
	};
}


