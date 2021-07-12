#pragma once
#include "mesh.h"
#include<vector>

using std::vector;
namespace GraphicsModule {
	class objeto;
	class model
	{
	public:
		std::map<string, unsigned int> m_BoneMapping;
		vector<mesh*> modelo;
		matrix* bones;
		matrix* bonesPos;
		matrix* bonesEskeleton;
		aiMatrix4x4 m_GlobalInverseTransform;
		int BonesNum = 0;
		const aiScene* m_pScene;
		Buffer BonesB;
		Buffer skeletonB;
		objeto* boneMesh = NULL;
		void add(mesh* m);
		void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
		const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
		void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform);
		void BoneTransform(float time);
		void makePalo(std::string Name,int n);
		void init();
		~model();

	};
}