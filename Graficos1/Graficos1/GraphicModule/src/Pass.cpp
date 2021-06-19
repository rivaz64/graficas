#ifdef openGL
#include<glm\gtc\type_ptr.hpp>
#endif
#include "Pass.h"
#include<iostream>
#include"manager.h"
int GraphicsModule::Pass::outn=0;
void GraphicsModule::Pass::render(std::vector<objeto*> objts)//)
{
    manager* man = getmanager();
#ifdef openGL
    if (ulti) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    else {
        glBindFramebuffer(GL_FRAMEBUFFER, ren.FramebufferName);
        for (int i = 0; i < outs.size(); i++) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, ren.DrawBuffers[i], GL_TEXTURE_2D, ren.rtv.textur[i].get,0);
        }
    }
    glUniform1i(glGetUniformLocation(man->actualchader, "texture1"), 0);
    glUniform1i(glGetUniformLocation(man->actualchader, "NormalMap"), 1);
    glUniform1i(glGetUniformLocation(man->actualchader, "SpecularMap"), 2);
    glUniform1i(glGetUniformLocation(man->actualchader, "Position"), 3);
    glUniform1i(glGetUniformLocation(man->actualchader, "AmbientOclucion"), 4);
    glUniform1i(glGetUniformLocation(man->actualchader, "cubemap"), 5);
#endif
    if (setear) {
        ren.setTargets();
        ren.clearTargets();
    }
#ifdef openGL
    glEnable(GL_CULL_FACE);
    glCullFace((GLenum)c);
    glFrontFace(GL_CCW);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        GLenum frame = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        int xyz = 1;
    }

#endif
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
        getmanager()->draw(i, vc[0], chaders[chadernum]);

    


    if (!ulti&&setear) {
        for (int i = 0; i < size; i++)
        {
#ifdef directX
            getmanager()->saves->material[outn]->srv = ren.rtv.srv[i];
            getmanager()->screen->material[outs[i]]->srv = ren.rtv.srv[i];
#endif
#ifdef openGL
            man->screen->material[outs[i]]->get = ren.rtv.textur[i].get;
            man->saves->material[outn]->get = ren.rtv.textur[i].get;
#endif
            outn++;

        }
    }

}

void GraphicsModule::Pass::compile(std::string file, std::vector<std::string> tecnicas, bool ultimo,vector<int> n, SRV_DIMENSION d, bool set, CULING cul) {
    ulti = ultimo;
    outs = n;
    size = n.size();
    setear = set;
    c = cul;
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