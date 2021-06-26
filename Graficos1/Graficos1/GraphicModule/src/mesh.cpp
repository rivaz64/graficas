#include "mesh.h"
#include"test.h"
void readmatrix(matrix& m, const aiMatrix4x4& aim) {
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
}
void readmatrix(XMMATRIX& m, const aiMatrix4x4& aim) {
    m._11 = aim.a1;
    m._12 = aim.a2;
    m._13 = aim.a3;
    m._14 = aim.a4;
    m._21 = aim.b1;
    m._22 = aim.b2;
    m._23 = aim.b3;
    m._24 = aim.b4;
    m._31 = aim.c1;
    m._32 = aim.c2;
    m._33 = aim.c3;
    m._34 = aim.c4;
    m._41 = aim.d1;
    m._42 = aim.d2;
    m._43 = aim.d3;
    m._44 = aim.d4;
}
void readmatrix(XMMATRIX& m, const matrix& aim) {
    m._11 = aim.m[0];
    m._12 = aim.m[1];
    m._13 = aim.m[2];
    m._14 = aim.m[3];
    m._21 = aim.m[4];
    m._22 = aim.m[5];
    m._23 = aim.m[6];
    m._24 = aim.m[7];
    m._31 = aim.m[8];
    m._32 = aim.m[9];
    m._33 = aim.m[10];
    m._34 = aim.m[11];
    m._41 = aim.m[12];
    m._42 = aim.m[13];
    m._43 = aim.m[14];
    m._44 = aim.m[15];
}
void readmatriz( matrix& aim, _XMMATRIX m) {
    aim.m[0] = m._11;
    aim.m[1] = m._12;
    aim.m[2] = m._13;
    aim.m[3] = m._14;
    aim.m[4] = m._21;
    aim.m[5] = m._22;
    aim.m[6] = m._23;
    aim.m[7] = m._24;
    aim.m[8] = m._31;
    aim.m[9] = m._32;
    aim.m[10] = m._33;
    aim.m[11] = m._34;
    aim.m[12] = m._41;
    aim.m[13] = m._42;
    aim.m[14] = m._43;
    aim.m[15] = m._44;
}
void readRotation(XMMATRIX& m, const aiMatrix3x3& aim) {
    m._11 = aim.a1;
    m._12 = aim.a2;
    m._13 = aim.a3;
    m._14 = 0;
    m._21 = aim.b1;
    m._22 = aim.b2;
    m._23 = aim.b3;
    m._24 = 0;
    m._31 = aim.c1;
    m._32 = aim.c2;
    m._33 = aim.c3;
    m._34 = 0;
    m._41 = 0;
    m._42 = 0;
    m._43 = 0;
    m._44 = 1;
}
namespace GraphicsModule {
    void mesh::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
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
    void mesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
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
    void mesh::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
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
    unsigned int mesh::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
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
    unsigned int mesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
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
    unsigned int mesh::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
    {
        for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
            if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
                return i;
            }
        }

        assert(0);

        return 0;
    }
    const aiNodeAnim* mesh::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
    {
        for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
            const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

            if (string(pNodeAnim->mNodeName.data) == NodeName) {
                return pNodeAnim;
            }
        }

        return NULL;
    }
    void mesh::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const matrix& ParentTransform)
    {
        string NodeName(pNode->mName.data);

        const aiAnimation* pAnimation = m_pScene->mAnimations[0];

        XMMATRIX NodeTransformation;
        readmatrix(NodeTransformation, pNode->mTransformation);
        const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

        if (pNodeAnim) {
            // Interpolate scaling and generate scaling transformation matrix
            aiVector3D Scaling;
            CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
            XMMATRIX ScalingM;
            ScalingM = XMMatrixScaling(Scaling.x, Scaling.y, Scaling.z);
            //ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);

            // Interpolate rotation and generate rotation transformation matrix
            aiQuaternion RotationQ;
            CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
            XMMATRIX RotationM;
            readRotation(RotationM, RotationQ.GetMatrix());

            // Interpolate translation and generate translation transformation matrix
            aiVector3D Translation;
            CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
            XMMATRIX TranslationM;
            TranslationM = XMMatrixTranslation(Translation.x, Translation.y, Translation.z);

            // Combine the above transformations
           
            NodeTransformation = TranslationM * RotationM * ScalingM;
        }

        XMMATRIX GlobalTransformation;
        XMMATRIX parent;
        readmatrix(parent, ParentTransform);

        GlobalTransformation= parent * NodeTransformation;
        XMMATRIX bonofset;
        XMVECTOR nein;
        if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
            unsigned int BoneIndex = m_BoneMapping[NodeName];
            readmatrix(bonofset, bones[BoneIndex].offset);
            //este va descomentado aka
            readmatriz(bones[BoneIndex].FinalTransformation,m_GlobalInverseTransform * GlobalTransformation * bonofset);
            //bones[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * bonofset;

        }
        matrix global;
        readmatriz(global, GlobalTransformation);
        for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
            ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], global);
        }//*/
    }
    void mesh::BoneTransform(float time)
    {
        XMMATRIX Identity = XMMatrixIdentity();

        /*float TicksPerSecond = (float)(m_pScene->mAnimations[0]->mTicksPerSecond != 0 ? m_pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
        float TimeInTicks = TimeInSeconds * TicksPerSecond;
        float AnimationTime = fmod(TimeInTicks, (float)m_pScene->mAnimations[0]->mDuration);//*/
        matrix iden;
        readmatriz(iden, Identity);
        ReadNodeHeirarchy(0, m_pScene->mRootNode, iden);

        

        for (int i = 0; i < BonesNum; i++) {
            bonesPos[i].ofset = bones[i].FinalTransformation;
        }

    }
    /*void mesh::ReadNodeHeriarchy(float time, const aiNode* pNode)
    {
        string NodeName(pNode->mName.data);
        const aiAnimation* pAnimation = scene->mAnimations[0];
        const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
        if (pNodeAnim) {
            aiVector3D Scaling;
            CalcInterpolatedScaling(Scaling, 0, pNodeAnim);
        }

    }*/
    Buffer* mesh::getindices()
    {
        return &indexB;
    }

    void mesh::setindices(std::initializer_list<unsigned int> i,int ni)
    {
        /*
        indexnum = ni;
        indices = (unsigned int*)i.begin();
        indexB.Usage = USAGE::DEFAULT;
        indexB.ByteWidth = sizeof(unsigned int)*ni;
        indexB.BindFlags = BIND_FLAG::INDEX_BUFFER;
        indexB.CPUAccessFlags = 0;
        indexB.Mem = indices;
        getmanager()->getDevice()->CreateBuffer(indexB);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
#ifdef directX
        bd.Usage = (D3D11_USAGE)USAGE::DEFAULT;
        bd.ByteWidth = sizeof(WORD) * 36;
        bd.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        InitData.pSysMem = indices;
        getmanager()->getDevice()->CreateBuffer(bd, InitData, indexB);
#endif//*/
    }

    Buffer* mesh::getvertex()
    {
        return &vertexB;
    }
    void mesh::setvertex(std::initializer_list<float> i,int num) {
        /*
#ifdef openGL
        n = num;
        points = (float*)i.begin();
        vertexB.BindFlags = GraphicsModule::BIND_FLAG::VERTEX_BUFFER;
        vertexB.Usage = GraphicsModule::USAGE::DEFAULT;
        vertexB.ByteWidth = sizeof(float)*n*5;
        vertexB.Mem = points;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        GraphicsModule::getmanager()->getDevice()->CreateBuffer(vertexB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        

#endif
*/
    }
    void mesh::setcolor(std::initializer_list<float> i)
    {
        /*
        colors = (float*)i.begin();
        GLunsigned int vertexbuffer;
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        colorB.BindFlags = GraphicsModule::BIND_FLAG::VERTEX_BUFFER;
        colorB.Usage = GraphicsModule::USAGE::DEFAULT;
        colorB.ByteWidth = sizeof(float) * n * 3;
        colorB.Mem = points;
        GraphicsModule::getmanager()->getDevice()->CreateBuffer(colorB);*/
    }
    void mesh::setvertex(std::initializer_list<vertex> i)
    {
        
#ifdef directX
        points = (vertex*)i.begin();
        D3D11_BUFFER_DESC bd;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = (D3D11_USAGE)USAGE::DEFAULT;
        bd.ByteWidth = sizeof(SimpleVertex) * 24;
        bd.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = points;
        getmanager()->getDevice()->CreateBuffer(bd, InitData, vertexB);
#endif
    }
    void mesh::init(int nv, int ni)
    {
        n = nv;
        vertexB.BindFlags = GraphicsModule::BIND_FLAG::VERTEX_BUFFER;
        vertexB.Usage = GraphicsModule::USAGE::DEFAULT;
        vertexB.ByteWidth = sizeof(vertex) * n;
        vertexB.Mem = points;

        indexnum = ni;
        indexB.BindFlags = BIND_FLAG::INDEX_BUFFER;
        indexB.Usage = USAGE::DEFAULT;
        indexB.ByteWidth = sizeof(unsigned int) * ni;
        indexB.CPUAccessFlags = 0;
        indexB.Mem = indices;


        
#ifdef openGL
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
#endif
        getmanager()->getDevice()->CreateBuffer(vertexB);
        getmanager()->getDevice()->CreateBuffer(indexB);

        if (BonesNum > 0) {
            BonesB.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
            BonesB.Usage = USAGE::DEFAULT;
            BonesB.ByteWidth = sizeof(Bone) * 1024;
            BonesB.CPUAccessFlags = 0;
            BonesB.Mem = bones;
            getmanager()->getDevice()->CreateBuffer(BonesB);
        }
#ifdef openGL
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 *sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
        glEnableVertexAttribArray(4);
#endif
        //delete[] vertexB.Mem;
        //delete[] points;
        //delete[] indices;
    }
    mesh::~mesh()
    {
        delete[] points;
        delete[] indices;
    }
}
