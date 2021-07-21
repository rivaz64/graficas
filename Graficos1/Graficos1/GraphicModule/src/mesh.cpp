#include "mesh.h"
#include"test.h"

namespace GraphicsModule {
    

    void mesh::readBones(const aiNode* pNode)
    {
        /*for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
            readBones(pNode->mChildren[i]);
        }*/
    }

    Buffer* mesh::getindices()
    {
        return &indexB;
    }



    Buffer* mesh::getvertex()
    {
        return &vertexB;
    }



    void mesh::init(int nv, int ni)
    {
        n = nv;
        vertexB.BindFlags = GraphicsModule::BIND_FLAG::VERTEX_BUFFER;
        vertexB.Usage = GraphicsModule::USAGE::DEFAULT;
        vertexB.ByteWidth = sizeof(vertex) * n;
        indexB.CPUAccessFlags = 0;
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
        vertexB.init();
        indexB.init();

        
#ifdef openGL
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 22 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 22 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 22 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 22 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 22 * sizeof(float), (void*)(11 * sizeof(float)));
        glEnableVertexAttribArray(4);
        glVertexAttribIPointer(5, 4, GL_INT, 22 * sizeof(float), (void*)(14 * sizeof(int)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 22 * sizeof(float), (void*)(18 * sizeof(float)));
        glEnableVertexAttribArray(6);
#endif
        //delete[] vertexB.Mem;
        //delete[] points;
        //delete[] indices;
    }
    aiNode* mesh::searchByName(std::string Name)
    {
        /*std::vector< aiNode*> actuals = { m_pScene->mRootNode };
        std::vector< aiNode*> nexts;
        while (actuals.size() > 0) {
            for (aiNode* node : actuals) {
                for (int i = 0; i < node->mNumChildren; i++) {
                    if (node->mChildren[i]->mName.C_Str() == Name) {
                        return node->mChildren[i];
                    }
                    nexts.push_back(node->mChildren[i]);
                }
            }
            actuals = nexts;
            nexts.clear();
        }*/
        return NULL;
    }
    void mesh::createSkeletalMesh() {
       
/*        std::map<std::string, unsigned int>::iterator it = m_BoneMapping.begin();
        boneMesh->points = new vertex[m_BoneMapping.size()];
        boneMesh->indices = new unsigned int[m_BoneMapping.size() * 2];
        for (std::map<std::string, unsigned int>::iterator it = m_BoneMapping.begin(); it != m_BoneMapping.end(); it++) {
            aiNode* nodo = searchByName(it->first);
            if (nodo->mNumChildren > 0) {
                showbones = true;
                boneMesh->points = new vertex[nodo->mNumChildren + 1];
                boneMesh->indices = new unsigned int[nodo->mNumChildren * 2];
                boneMesh->points[0].boneid[0] = it->second;
                for (int i = 0; i < nodo->mNumChildren; i++) {
                    boneMesh->points[i + 1].boneid[0] = m_BoneMapping[nodo->mChildren[i]->mName.C_Str()];
                    boneMesh->indices[i * 2] = 0;
                    boneMesh->indices[i * 2 + 1] = 1;
                }

            }
        }
        
        boneMesh->init(2, 2);*/
        
    }
    mesh::~mesh()
    {
        delete[] points;
        delete[] indices;
        
    }
}
