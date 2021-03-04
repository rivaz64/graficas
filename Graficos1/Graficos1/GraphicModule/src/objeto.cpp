#include"objeto.h"
namespace GraphicsModule {
    void objeto::setTexture(RenderTargetView rtv)
    {
        tx->srv = rtv.srv;
    }
}