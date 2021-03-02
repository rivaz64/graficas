#include "DepthStencil.h"
#include"flags.h"
namespace GraphicsModule {
    void DepthStencil::descrivetextur()
    {
        textur.describe();
    }

    void DepthStencil::describeview()
    {
        ZeroMemory(&des, sizeof(des));
        des.Format = (DXGI_FORMAT)FORMAT::FLOAT;
        des.ViewDimension = (D3D11_DSV_DIMENSION)DIMENSION::TEXTURE2D;
        des.Texture2D.MipSlice = 0;
    }


}
