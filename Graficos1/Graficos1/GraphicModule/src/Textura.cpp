#include "Textura.h"
#include "manager.h"
#include"flags.h"
namespace GraphicsModule {
    void Textura::describe()
    {
        ZeroMemory(&des, sizeof(des));
        des.Width = getmanager()->width;
        des.Height = getmanager()->height;
        des.MipLevels = 1;
        des.ArraySize = 1;
        des.Format = (DXGI_FORMAT)FORMAT::TYPELESS;
        des.SampleDesc.Count = 1;
        des.SampleDesc.Quality = 0;
        des.Usage = (D3D11_USAGE)USAGE::DEFAULT;
        des.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::DEPTH_STENCIL | (D3D11_BIND_FLAG)BIND_FLAG::SHADER_RESOURCE;
        des.CPUAccessFlags = 0;
        des.MiscFlags = 0;
    }
}

