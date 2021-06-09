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
        getmanager()->getConext()->get()->VSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
    for (std::pair<int, Buffer*> p : pc) {
        getmanager()->getConext()->get()->PSSetConstantBuffers(p.first, 1, &p.second->buf);
    }
    for (GraphicsModule::objeto* i : objts)
        getmanager()->draw(i,vc[0], chaders[chadernum]);
    if (!ulti&&setear) {
        for (int i = 0; i < size; i++)
        {
            getmanager()->saves->material[outn]->srv = ren.rtv.srv[i];
            getmanager()->screen->material[outs[i]]->srv = ren.rtv.srv[i];
            outn++;
        }
        
    }
}

void GraphicsModule::Pass::compile(std::string file, std::vector<std::string> tecnicas, bool ultimo,vector<int> n, SRV_DIMENSION d, bool set) {
    ulti = ultimo;
    outs = n;
    size = n.size();
    setear = set;
    if (ultimo) {
        ren.init(FORMAT::UNKNOWN, FORMAT::FLOAT, false, n.size(),d);
    }
    else {
        ren.init(FORMAT::R32G32B32A32_FLOAT, FORMAT::UNORM_S8_UINT, true, n.size(),d);
    }
    for (int i = 0; i < tecnicas.size(); i++) {
        chaders.push_back(chader());
        chaders[i].compile(file, tecnicas[i]);
    }
}