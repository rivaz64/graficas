#include "mesh.h"
#include"test.h"
namespace GraphicsModule {
    Buffer* mesh::getindices()
    {
        return &indexB;
    }

    void mesh::setindices(std::initializer_list<unsigned int> i,int ni)
    {
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
        D3D11_BUFFER_DESC bd;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = (D3D11_USAGE)USAGE::DEFAULT;
        bd.ByteWidth = sizeof(WORD) * 36;
        bd.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        InitData.pSysMem = indices;
        getmanager()->getDevice()->CreateBuffer(bd, InitData, indexB);
#endif
    }

    Buffer* mesh::getvertex()
    {
        return &vertexB;
    }
    void mesh::setvertex(std::initializer_list<float> i,int num) {
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
    }
    void mesh::setcolor(std::initializer_list<float> i)
    {
        colors = (float*)i.begin();
        GLuint vertexbuffer;
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        colorB.BindFlags = GraphicsModule::BIND_FLAG::VERTEX_BUFFER;
        colorB.Usage = GraphicsModule::USAGE::DEFAULT;
        colorB.ByteWidth = sizeof(float) * n * 3;
        colorB.Mem = points;
        GraphicsModule::getmanager()->getDevice()->CreateBuffer(colorB);
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
        vertexB.ByteWidth = sizeof(float) * n * 5;
        vertexB.Mem = points;
        indexnum = ni;
        indexB.Usage = USAGE::DEFAULT;
        indexB.ByteWidth = sizeof(unsigned int) * ni;
        indexB.BindFlags = BIND_FLAG::INDEX_BUFFER;
        indexB.CPUAccessFlags = 0;
        indexB.Mem = indices;
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        getmanager()->getDevice()->CreateBuffer(vertexB);
        getmanager()->getDevice()->CreateBuffer(indexB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

    }
}
