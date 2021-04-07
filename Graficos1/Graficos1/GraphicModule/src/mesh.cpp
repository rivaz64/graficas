#include "mesh.h"
#include"test.h"
namespace GraphicsModule {
    Buffer* mesh::getindices()
    {
        return &indexB;
    }

    void mesh::setindices(std::initializer_list<short> i)
    {
        indices = (int*)i.begin();
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

    void mesh::setvertex(std::initializer_list<vertex> i)
    {
        points = (vertex*)i.begin();
#ifdef directX
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
        indexnum = ni;
        vertexB.Usage = USAGE::DEFAULT;
        vertexB.ByteWidth = sizeof(SimpleVertex) * nv;
        vertexB.BindFlags = BIND_FLAG::VERTEX_BUFFER;
        vertexB.CPUAccessFlags = 0;
        vertexB.Mem = points;
        indexB.Usage = USAGE::DEFAULT;
        indexB.ByteWidth = sizeof(int) * ni;
        indexB.BindFlags = BIND_FLAG::INDEX_BUFFER;
        indexB.CPUAccessFlags = 0;
        indexB.Mem = indices;
        getmanager()->getDevice()->CreateBuffer(vertexB);
        getmanager()->getDevice()->CreateBuffer(indexB);


    }
}
