#include"objeto.h"
namespace GraphicsModule {
    void objeto::setTexture(RenderTargetView rtv)
    {
#ifdef directX
        tx->srv = rtv.srv;
#endif

    }
    void objeto::setTexture(unsigned int t)
    {
        tx = new Textura;
        tx->get = t;
    }
}