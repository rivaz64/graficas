#include "model.h"
#include "manager.h"
#include "mesh.h"
#include <iostream>
#include "objeto.h"
void readmatrix(matrix& m, const aiMatrix4x4& aim) {
#ifdef openGL
    m.m[0].x = aim.a1;
    m.m[1].x = aim.a2;
    m.m[2].x = aim.a3;
    m.m[3].x = aim.a4;
    m.m[0].y = aim.b1;
    m.m[1].y = aim.b2;
    m.m[2].y = aim.b3;
    m.m[3].y = aim.b4;
    m.m[0].z = aim.c1;
    m.m[1].z = aim.c2;
    m.m[2].z = aim.c3;
    m.m[3].z = aim.c4;
    m.m[0].w = aim.d1;
    m.m[1].w = aim.d2;
    m.m[2].w = aim.d3;
    m.m[3].w = aim.d4;

#endif
#ifdef directX
    m.m[0] = aim.a1;
    m.m[1] = aim.a2;
    m.m[2] = aim.a3;
    m.m[3] = aim.a4;
    m.m[4] = aim.b1;
    m.m[5] = aim.b2;
    m.m[6] = aim.b3;
    m.m[7] = aim.b4;
    m.m[8] = aim.c1;
    m.m[9] = aim.c2;
    m.m[10] = aim.c3;
    m.m[11] = aim.c4;
    m.m[12] = aim.d1;
    m.m[13] = aim.d2;
    m.m[14] = aim.d3;
    m.m[15] = aim.d4;
#endif
}

void readmatrix(aiMatrix4x4& aim, matrix& m) {
#ifdef openGL
    aim.a1 = m.m[0].x;
    aim.a2 = m.m[1].x;
    aim.a3 = m.m[2].x;
    aim.a4 = m.m[3].x;
    aim.b1 = m.m[0].y;
    aim.b2 = m.m[1].y;
    aim.b3 = m.m[2].y;
    aim.b4 = m.m[3].y;
    aim.c1 = m.m[0].z;
    aim.c2 = m.m[1].z;
    aim.c3 = m.m[2].z;
    aim.c4 = m.m[3].z;
    aim.d1 = m.m[0].w;
    aim.d2 = m.m[1].w;
    aim.d3 = m.m[2].w;
    aim.d4 = m.m[3].w;
#endif
#ifdef directX
    aim.a1 = m.m[0];
    aim.a2 = m.m[1];
    aim.a3 = m.m[2];
    aim.a4 = m.m[3];
    aim.b1 = m.m[4];
    aim.b2 = m.m[5];
    aim.b3 = m.m[6];
    aim.b4 = m.m[7];
    aim.c1 = m.m[8];
    aim.c2 = m.m[9];
    aim.c3 = m.m[10];
    aim.c4 = m.m[11];
    aim.d1 = m.m[12];
    aim.d2 = m.m[13];
    aim.d3 = m.m[14];
    aim.d4 = m.m[15];
#endif
}


void readRotation(aiMatrix4x4& m, const aiMatrix3x3t<ai_real>& aim) {
    m.a1 = aim.a1;
    m.a2 = aim.a2;
    m.a3 = aim.a3;
    m.a4 = 0;
    m.b1 = aim.b1;
    m.b2 = aim.b2;
    m.b3 = aim.b3;
    m.b4 = 0;
    m.c1 = aim.c1;
    m.c2 = aim.c2;
    m.c3 = aim.c3;
    m.c4 = 0;
    m.d1 = 0;
    m.d2 = 0;
    m.d3 = 0;
    m.d4 = 1;
}
void GraphicsModule::model::add(mesh* m)
{
	modelo.push_back(m);
}
GraphicsModule::model::~model()
{
	for (mesh* m : modelo) {
		delete m;
	}
    if (boneMesh) {
        delete boneMesh;
    }
}
namespace GraphicsModule {
    void model::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        if (pNodeAnim->mNumScalingKeys == 1) {
            Out = pNodeAnim->mScalingKeys[0].mValue;
            return;
        }

        unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
        unsigned int  NextScalingIndex = (ScalingIndex + 1);
        assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
        float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
        const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
        aiVector3D Delta = End - Start;
        Out = Start + Factor * Delta;
    }
    void model::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        if (pNodeAnim->mNumRotationKeys == 1) {
            Out = pNodeAnim->mRotationKeys[0].mValue;
            return;
        }

        unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
        unsigned int NextRotationIndex = (RotationIndex + 1);
        assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
        float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
        const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
        aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
        Out = Out.Normalize();
    }
    void model::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        if (pNodeAnim->mNumPositionKeys == 1) {
            Out = pNodeAnim->mPositionKeys[0].mValue;
            return;
        }

        unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
        unsigned int NextPositionIndex = (PositionIndex + 1);
        assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
        float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
        const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
        aiVector3D Delta = End - Start;
        Out = Start + Factor * Delta;
    }
    unsigned int model::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        assert(pNodeAnim->mNumScalingKeys > 0);

        for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
            if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
                return i;
            }
        }

        assert(0);

        return 0;
    }
    unsigned int model::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        assert(pNodeAnim->mNumRotationKeys > 0);

        for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
            if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
                return i;
            }
        }

        assert(0);

        return 0;
    }
    unsigned int model::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
            if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
                return i;
            }
        }

        assert(0);

        return 0;
    }
    const aiNodeAnim* model::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
    {
        for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
            const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

            if (string(pNodeAnim->mNodeName.data) == NodeName) {
                return pNodeAnim;
            }
        }

        return NULL;
    }
    void model::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform)
    {
        string NodeName(pNode->mName.data);

        const aiAnimation* pAnimation = m_pScene->mAnimations[0];
        aiMatrix4x4 NodeTransformation;
        NodeTransformation = pNode->mTransformation;
        const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

        if (pNodeAnim && getmanager()->tpose) {
            // Interpolate scaling and generate scaling transformation matrix
            aiVector3D Scaling;
            CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
            aiMatrix4x4 ScalingM;
            ScalingM.a1 = Scaling.x;
            ScalingM.b2 = Scaling.y;
            ScalingM.c3 = Scaling.z;
            //ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);

            // Interpolate rotation and generate rotation transformation matrix
            aiQuaternion RotationQ;
            CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);

            //readRotation(RotationM, RotationQ.GetMatrix());
            aiMatrix4x4 RotationM;
            readRotation(RotationM, RotationQ.GetMatrix());
            // Interpolate translation and generate translation transformation matrix
            aiVector3D Translation;
            CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);

            aiMatrix4x4 TranslationM;
            TranslationM.a4 = Translation.x;
            TranslationM.b4 = Translation.y;
            TranslationM.c4 = Translation.z;
            // Combine the above transformations

            NodeTransformation = TranslationM * RotationM * ScalingM;
        }//*/

        aiMatrix4x4 GlobalTransformation;

        GlobalTransformation = ParentTransform * NodeTransformation;
        aiMatrix4x4 bonofset;
        if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
            unsigned int BoneIndex = m_BoneMapping[NodeName];
            readmatrix(bonofset, bones[BoneIndex]);
            readmatrix(bonesPos[BoneIndex], m_GlobalInverseTransform * GlobalTransformation * bonofset);
            readmatrix(bonesEskeleton[BoneIndex], m_GlobalInverseTransform * GlobalTransformation);
        }
        for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
            ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
        }//*/
    }
    void model::BoneTransform(float time)
    {

        float TicksPerSecond = (float)(m_pScene->mAnimations[0]->mTicksPerSecond != 0 ? m_pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
        float TimeInTicks = time * TicksPerSecond;
        float AnimationTime = fmod(TimeInTicks, (float)m_pScene->mAnimations[0]->mDuration);//*/
        matrix iden;
        aiMatrix4x4 ide;

        readmatrix(ide, iden);
        ReadNodeHeirarchy(AnimationTime, m_pScene->mRootNode, ide);
    }

    void model::makePalo(std::string Name, int n)
    {
        std::vector< aiNode*> actuals = { m_pScene->mRootNode };
        std::vector< aiNode*> nexts;
        int nu = -1;
        while (actuals.size() > 0) {
            for (aiNode* node : actuals) {
                for (int i = 0; i < node->mNumChildren; i++) {
                    if (node->mChildren[i]->mName.C_Str() == Name) {
                        if (m_BoneMapping.find(node->mName.C_Str()) != m_BoneMapping.end()) {
                            boneMesh->mod->modelo[0]->indices[n * 2] = n;
                            
                            for (std::map<std::string, unsigned int>::iterator it = m_BoneMapping.begin(); it != m_BoneMapping.end(); it++) {
                                nu++;
                                if (node->mName.C_Str() == it->first) {
                                    break;
                                }
                            }
                            boneMesh->mod->modelo[0]->indices[n * 2 + 1] = nu;
                            //std::cout <<Name<< " "<< n << " " << node->mName.C_Str()<<" "<< nu << std::endl;
                        }
                        return;
                    }
                    nexts.push_back(node->mChildren[i]);
                }
            }
            actuals = nexts;
            nexts.clear();
        }
    }

    

    void model::init() {
        if (BonesNum > 0) {
            BonesB.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
            BonesB.Usage = USAGE::DEFAULT;
            BonesB.ByteWidth = sizeof(matrix) * 32;
            BonesB.CPUAccessFlags = 0;
            BonesB.Mem = bones;
            BonesB.init();
            skeletonB.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
            skeletonB.Usage = USAGE::DEFAULT;
            skeletonB.ByteWidth = sizeof(matrix) * 32;
            skeletonB.CPUAccessFlags = 0;
            skeletonB.Mem = bones;
            skeletonB.init();
            

            bonesEskeleton = new matrix[32];

            boneMesh = new objeto;
            boneMesh->mod = new model;
            boneMesh->mod->modelo.push_back(new mesh);
            boneMesh->mod->modelo[0]->points = new mesh::vertex[m_BoneMapping.size()];
            boneMesh->mod->modelo[0]->indices = new unsigned int[m_BoneMapping.size() * 2];
            int n = 0;
            for (std::map<std::string, unsigned int>::iterator it = m_BoneMapping.begin(); it != m_BoneMapping.end(); it++) {
                //std::cout << it->first << std::endl;
                boneMesh->mod->modelo[0]->points[n].boneid[0] = it->second;
                boneMesh->mod->modelo[0]->points[n].Weight[0] = 1;
                makePalo(it->first, n);
                n++;
                //if(n==5)
                //break;
            }
            boneMesh->mod->modelo[0]->init(m_BoneMapping.size(), m_BoneMapping.size() * 2);
            getmanager()->skeletons->push_back(boneMesh);
        }
        
    }
}
