#ifdef openGL
#include<glm\gtc\type_ptr.hpp>
#endif
#include "Pass.h"
#include<iostream>
#include"manager.h"
int GraphicsModule::Pass::outn=0;
void GraphicsModule::Pass::render(std::vector<objeto*>* objts,bool bol)//)
{
    manager* man = getmanager();
#ifdef openGL
    if (ulti) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    else {
        glBindFramebuffer(GL_FRAMEBUFFER, ren.FramebufferName);
        for (int i = 0; i < outs.size(); i++) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, ren.DrawBuffers[i], GL_TEXTURE_2D, ren.rtv.textur[i].srv.get,0);
        }
    }
    glUniform1i(glGetUniformLocation(man->actualchader, "texture1"), 0);
    glUniform1i(glGetUniformLocation(man->actualchader, "NormalMap"), 1);
    glUniform1i(glGetUniformLocation(man->actualchader, "SpecularMap"), 2);
    glUniform1i(glGetUniformLocation(man->actualchader, "Position"), 3);
    glUniform1i(glGetUniformLocation(man->actualchader, "AmbientOclucion"), 4);
    glUniform1i(glGetUniformLocation(man->actualchader, "cubemap"), 5);
#endif

    if (clear) {//aka47
        ren.setTargets();
        ren.clearTargets(clear);
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

    man->actualPrimitiveTopology = primitiveTopology;
   
    if(vc.size()>1)
    for (std::pair<int, Buffer*> p : vc) {
        if (!p.second) {
            int x=0;
        }
        getmanager()->getConext()->VSSetConstantBuffers(p.first,p.second);
    }
    for (std::pair<int, Buffer*> p : pc) {
        getmanager()->getConext()->PSSetConstantBuffers(p.first, p.second);
    }
    for (std::pair<int, Textura*> p : pt) {
        getmanager()->getConext()->PSSetShaderResources(p.second, p.first);
    }
    if(objts)
    for (GraphicsModule::objeto* i : *objts)
        getmanager()->draw(i, vc[0], chaders[chadernum]);

    


    if (!ulti&&true) {//aka47
        for (int i = 0; i < size; i++)
        {
            man->saves->mod->modelo[0]->material[outn]->srv = man->actualRen->rtv.srv[i];
            man->screen->mod->modelo[0]->material[outs[i]]->srv = man->actualRen->rtv.srv[i];
            outn++;

        }
    }

}

void GraphicsModule::Pass::compile(std::string file, std::vector<std::string> tecnicas, bool ultimo,vector<int> n, CULING cul, PRIMITIVE_TOPOLOGY p) {
    ulti = ultimo;
    outs = n;
    size = n.size();
    c = cul;
    primitiveTopology = p;
    if (ultimo) {
        ren.init(FORMAT::UNKNOWN, FORMAT::FLOAT, false, n.size(), SRV_DIMENSION::TEXTURE2D,cul);
    }
    else {
        ren.init(FORMAT::R32G32B32A32_FLOAT, FORMAT::UNORM_S8_UINT, true, n.size(), SRV_DIMENSION::TEXTURE2D, cul);
    }
    for (int i = 0; i < tecnicas.size(); i++) {
        chaders.push_back(chader());
        chaders[i].compile(file, tecnicas[i]);
    }
}