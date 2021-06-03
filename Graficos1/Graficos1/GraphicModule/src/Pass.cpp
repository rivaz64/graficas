#include "Pass.h"
#include<iostream>
#include"manager.h"
bool  GraphicsModule::Pass::first=true;
void GraphicsModule::Pass::render(std::vector<objeto*>& objts)//)
{
    
    //getmanager()->draw()
    ren.setTargets();
    ren.clearTargets();
    chaders[chadernum].setShader();
    for (std::pair<int, Buffer*> p : vc) {
        getmanager()->getConext()->get()->VSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
    for (std::pair<int, Buffer*> p : pc) {
        getmanager()->getConext()->get()->PSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
    for (GraphicsModule::objeto* i : objts)
        getmanager()->draw(i,vc[0], chaders[chadernum]);
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