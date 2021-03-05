#include "Textura.h"
#include "manager.h"

namespace GraphicsModule {
    void Textura::describe(FORMAT f, BIND_FLAG bf)
    {
        ZeroMemory(&des, sizeof(des));
        des.Width = getmanager()->width;
        des.Height = getmanager()->height;
        des.MipLevels = 1;
        des.ArraySize = 1;
        des.Format = (DXGI_FORMAT)f;
        des.SampleDesc.Count = 1;
        des.SampleDesc.Quality = 0;
        des.Usage = (D3D11_USAGE)USAGE::DEFAULT;
        des.BindFlags = (D3D11_BIND_FLAG)bf | (D3D11_BIND_FLAG)BIND_FLAG::SHADER_RESOURCE;
        des.CPUAccessFlags = 0;
        des.MiscFlags = 0;
    }
    void Textura::loadfromfile(LPCSTR f)
    {
#ifdef directX
        D3DX11CreateShaderResourceViewFromFile(getmanager()->getDevice()->get(), f, NULL, NULL, &srv, NULL);
#endif
    }
    
}
