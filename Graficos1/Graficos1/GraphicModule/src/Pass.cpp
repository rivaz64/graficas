#include "Pass.h"
#include<iostream>
#include"manager.h"
void GraphicsModule::Pass::render(std::vector<objeto*> objts)//)
{
    ren.setTargets();
    ren.clearTargets();
    chaders[chadernum].setShader();
    if(vc.size()>1)
    for (std::pair<int, Buffer*> p : vc) {
        getmanager()->getConext()->get()->VSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
    for (std::pair<int, Buffer*> p : pc) {
        getmanager()->getConext()->get()->PSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
    for (GraphicsModule::objeto* i : objts)
        getmanager()->draw(i,vc[0], chaders[chadernum]);
    if (!ulti) {
        for(int i=0;i<size;i++)
        getmanager()->screen->material[outs[i]]->srv = ren.rtv.srv[i];
        //aka 47
    }
}

void GraphicsModule::Pass::compile(std::string file, std::vector<std::string> tecnicas, bool ultimo,vector<int> n) {
    ulti = ultimo;
    outs = n;
    size = n.size();
    if (ultimo) {
        ren.init(FORMAT::UNKNOWN, FORMAT::FLOAT, false, n.size());
    }
    else {
        ren.init(FORMAT::R32G32B32A32_FLOAT, FORMAT::UNORM_S8_UINT, true, n.size());
    }
    for (int i = 0; i < tecnicas.size(); i++) {
        chaders.push_back(chader());
        chaders[i].compile(file, tecnicas[i]);
    }
}