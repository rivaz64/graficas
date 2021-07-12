#pragma once
#include <initializer_list>
#include"Buffer.h"
#include"Textura.h"
#include "camera.h"
#include<vector>
#include"assimp\Importer.hpp"
#include"assimp\scene.h"
#include<map>

//#include <chrono>
#define NUM_BONES_PER_VEREX 1024
namespace GraphicsModule {
	class mesh
	{
		
	public:
		
		struct vertex {
			float posi[3] = { 0,0,0 };
			float uv[2] = { 0,0 };;
			float normal[3] = { 0,0,0 };
			float binormal[3] = { 0,0,0 };
			float tangent[3] = { 0,0,0 };
			int boneid[4] = { 0 ,0 ,0 ,0 };
			float Weight[4] = {0.0f ,0.0f ,0.0f ,0.0f };
		};
		mesh() {}
		~mesh();
		int indexnum;
		
		vertex* points;
		
		mesh* boneMesh=NULL;
		
		unsigned int* indices;
		std::vector<Textura*> material;
		int numaterial = 0;
		Buffer vertexB;
		Buffer indexB;
		
		Buffer colorB;
		unsigned int vao;
		int n = 0;
		
		bool showbones=false;
		void readBones(const aiNode* pNode );
		void createSkeletalMesh();
		Buffer* getindices();
		Buffer* getvertex();
		void init(int nv, int ni);
		aiNode* searchByName(std::string Name);
	};
}


