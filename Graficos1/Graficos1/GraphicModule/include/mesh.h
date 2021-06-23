#pragma once
#include <initializer_list>
#include"Buffer.h"
#include"Textura.h"
#include "camera.h"
#include<vector>
namespace GraphicsModule {
	class mesh
	{
		
	public:
		struct Bone {
			const char* name;
			matrix offset;
		};
		struct vertex {
			float posi[3];
			float uv[2];
			float normal[3];
			float binormal[3];
			float tangent[3];
		};
		mesh() {}
		~mesh();
		int indexnum;
		int BonesNum = 0;
		vertex* points;
		Bone* bones;

		unsigned int* indices;
		Buffer vertexB;
		Buffer indexB;
		Buffer colorB;
		unsigned int vao;
		Buffer* getindices();
		
		int n = 0;
		void setindices(std::initializer_list<unsigned int> i,int in);
		Buffer* getvertex();
		void setvertex(std::initializer_list<vertex> i);
		void setvertex(std::initializer_list<float> i,int num);
		void setcolor(std::initializer_list<float> i);
		void init(int nv, int ni);
	};
}


