#include"objeto.h"
namespace GraphicsModule {
    void objeto::setTexture(RenderTargetView rtv)
    {
#ifdef directX
        //mod->modelo[0]->material[0]->srv= rtv.srv;
#endif

    }
    void objeto::setTexture(unsigned int t)
    {
#ifdef openGL
        //tx = new Textura;
        //tx->get = t;
#endif
    }
    objeto::~objeto()
    {
        /*for (Textura* t : material) {
            delete t;
        }*/
        delete mod;
    }
}