#include "Pass.h"

void GraphicsModule::Pass::render()
{
#ifdef directX
    for (std::pair<int, Buffer*> p : vc) {
        getmanager()->getConext()->get()->VSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
    for (std::pair<int, Buffer*> p : pc) {
        getmanager()->getConext()->get()->PSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
    /*for (std::pair<int, Buffer*> p : pt) {
        getmanager()->getConext()->get()->PSSetShaderResources(p.first, 1, &p.second->buf);
    }*/
#endif
    
}
