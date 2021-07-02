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
		struct Bone {
			matrix offset;
		};
		struct BoneInfo {
			matrix offset;
			matrix FinalTransformation;
		};
		struct vertex {
			float posi[3];
			float uv[2];
			float normal[3];
			float binormal[3];
			float tangent[3];
			int boneid[4] = { 0 ,0 ,0 ,0 };
			float Weight[4] = {0.0f ,0.0f ,0.0f ,0.0f };
		};
		mesh() {}
		~mesh();
		int indexnum;
		int BonesNum = 0;
		vertex* points;
		Bone* bones;
		Bone* bonesPos;
		aiMatrix4x4 m_GlobalInverseTransform;
		//BoneData* databones;
		unsigned int* indices;
		std::vector<Textura*> material;
		int numaterial = 0;
		Buffer vertexB;
		Buffer indexB;
		Buffer BonesB;
		Buffer colorB;
		unsigned int vao;
		int n = 0;
		float timer = 0;
		const aiScene* m_pScene;
		std::map<string, unsigned int> m_BoneMapping;
		void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
		const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
		void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform);

		void BoneTransform(float time);
		//void ReadNodeHeriarchy(float time, const aiNode* pNode);
		Buffer* getindices();
		void setindices(std::initializer_list<unsigned int> i,int in);
		Buffer* getvertex();
		void setvertex(std::initializer_list<vertex> i);
		void setvertex(std::initializer_list<float> i,int num);
		void setcolor(std::initializer_list<float> i);
		void init(int nv, int ni);
	};
}


