#include"objeto.h"
namespace GraphicsModule {
    void objeto::setTexture(RenderTargetView rtv)
    {
#ifdef directX
        tx->srv = rtv.srv;
#endif
    }
}