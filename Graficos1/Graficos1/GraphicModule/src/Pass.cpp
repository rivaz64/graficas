#ifdef openGL
#include<glm\gtc\type_ptr.hpp>
#endif
#include "Pass.h"
#include<iostream>
#include"manager.h"
int GraphicsModule::Pass::outn=0;
void GraphicsModule::Pass::render(std::vector<objeto*> objts)//)
{
    if (setear) {
        ren.setTargets();
        ren.clearTargets();
    }
    chaders[chadernum].setShader();
    if(vc.size()>1)
    for (std::pair<int, Buffer*> p : vc) {
        getmanager()->getConext()->VSSetConstantBuffers(p.first,p.second);
    }
    for (std::pair<int, Buffer*> p : pc) {
        getmanager()->getConext()->PSSetConstantBuffers(p.first, p.second);
    }
    for (std::pair<int, Textura*> p : pt) {
        getmanager()->getConext()->PSSetShaderResources(p.second, p.first);
    }
    for (GraphicsModule::objeto* i : objts)
        getmanager()->draw(i,vc[0], chaders[chadernum]);
    if (!ulti&&setear) {
        for (int i = 0; i < size; i++)
        {
#ifdef directX
            getmanager()->saves->material[outn]->srv = ren.rtv.srv[i];
            getmanager()->screen->material[outs[i]]->srv = ren.rtv.srv[i];
            outn++;
#endif
        }
        
    }
}

void GraphicsModule::Pass::compile(std::string file, std::vector<std::string> tecnicas, bool ultimo,vector<int> n, SRV_DIMENSION d, bool set, CULING cul) {
    ulti = ultimo;
    outs = n;
    size = n.size();
    setear = set;
    if (ultimo) {
        ren.init(FORMAT::UNKNOWN, FORMAT::FLOAT, false, n.size(),d,cul);
    }
    else {
        ren.init(FORMAT::R32G32B32A32_FLOAT, FORMAT::UNORM_S8_UINT, true, n.size(),d, cul);
    }
    for (int i = 0; i < tecnicas.size(); i++) {
        chaders.push_back(chader());
        chaders[i].compile(file, tecnicas[i]);
    }
}