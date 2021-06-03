#include "Pass.h"
#include<iostream>
bool  GraphicsModule::Pass::first=true;
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
    if (first) {
        first = false;
        ren.init(FORMAT::UNKNOWN, FORMAT::FLOAT, false);
    }
    for (int i = 0; i < tecnicas.size(); i++) {
        chaders.push_back(chader());
        chaders[i].compile(file, tecnicas[i]);
    }
}