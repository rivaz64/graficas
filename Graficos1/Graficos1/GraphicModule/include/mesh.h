#pragma once
#include <initializer_list>
#include"Buffer.h"
namespace GraphicsModule {
	class mesh
	{
		
	public:
		struct vertex {
			float posi[3];
			float uv[2];
			float normal[3];
		};
		int indexnum;
		vertex* points;
		int* indices;
		Buffer vertexB;
		Buffer indexB;
		Buffer* getindices();
		void setindices(std::initializer_list<short> i);
		Buffer* getvertex();
		void setvertex(std::initializer_list<vertex> i);
		void init(int nv, int ni);
	};
}


