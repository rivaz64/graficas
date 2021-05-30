#include "DepthStencil.h"
#include"flags.h"
namespace GraphicsModule {
    void DepthStencil::descrivetextur()
    {
        textur.describe(FORMAT::FLOAT, BIND_FLAG::DEPTH_STENCIL);
    }

    void DepthStencil::describeview()
    {
#ifdef directX
        ZeroMemory(&des, sizeof(des));
        des.Format = (DXGI_FORMAT)textur.des.Format;
        des.ViewDimension = (D3D11_DSV_DIMENSION)DIMENSION::TEXTURE2D;
        des.Texture2D.MipSlice = 0;
#endif
    }


}
