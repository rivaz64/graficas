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
		mesh() {}
		int indexnum;
		vertex* points;


		unsigned int* indices;
		Buffer vertexB;
		Buffer indexB;
		Buffer colorB;
		unsigned int vao;
		Buffer* getindices();
		float* colors;
		int n = 0;
		void setindices(std::initializer_list<unsigned int> i,int in);
		Buffer* getvertex();
		void setvertex(std::initializer_list<vertex> i);
		void setvertex(std::initializer_list<float> i,int num);
		void setcolor(std::initializer_list<float> i);
		void init(int nv, int ni);
	};
}


