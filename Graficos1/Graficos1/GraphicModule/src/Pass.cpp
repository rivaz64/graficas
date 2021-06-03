#include "Pass.h"
#include<iostream>
void GraphicsModule::Pass::render()
{
    chaders[chadernum].setShader();
    for (std::pair<int, Buffer*> p : vc) {
        getmanager()->getConext()->get()->VSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
    for (std::pair<int, Buffer*> p : pc) {
        getmanager()->getConext()->get()->PSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
}
void GraphicsModule::Pass::compile(std::string file, std::vector<std::string> tecnicas) {
    std::cout << 'o' << std::endl;
}