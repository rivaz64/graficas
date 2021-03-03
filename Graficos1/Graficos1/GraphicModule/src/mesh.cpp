#include "mesh.h"
#include"test.h"
namespace GraphicsModule {
    short* mesh::getindices()
    {
        return indices;
    }

    void mesh::setindices(std::initializer_list<short> i)
    {
        indices = (short*)i.begin();
    }

    Buffer* mesh::getvertex()
    {
        return &vertexB;
    }

    void mesh::setvertex(std::initializer_list<vertex> i)
    {
        points = (vertex*)i.begin();
        
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = (D3D11_USAGE)USAGE::DEFAULT;
        bd.ByteWidth = sizeof(SimpleVertex) * 24;
        bd.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = points;
        getmanager()->getDevice()->CreateBuffer(bd, InitData, vertexB);
    }

}
