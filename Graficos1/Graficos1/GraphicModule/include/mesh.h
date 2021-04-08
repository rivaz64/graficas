#pragma once
#include <initializer_list>
#include"Buffer.h"
namespace GraphicsModule {
	class mesh
	{
		
	public:
		struct vertex {

			float posi[3];
#ifdef directX
			float uv[2];
			float normal[3];
#endif
		};
		mesh() {}
		int indexnum;
#ifdef openGL
		float* points;
#endif
#ifdef directX
		vertex* points;
#endif
		int* indices;
		Buffer vertexB;
		Buffer indexB;
		unsigned int vao;
		Buffer* getindices();
		
		int n = 0;
		void setindices(std::initializer_list<short> i);
		Buffer* getvertex();
		void setvertex(std::initializer_list<vertex> i);
		void setvertex(std::initializer_list<float> i,int num);
		void init(int nv, int ni);
	};
}


