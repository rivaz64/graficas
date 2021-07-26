#include "Textura.h"
#include "manager.h"

#include"TextureManager.h"
namespace GraphicsModule {
    void Textura::describe(FORMAT f, BIND_FLAG bf)
    {
#ifdef directX
        ZeroMemory(&des, sizeof(des));
        des.Width = getmanager()->width;
        des.Height = getmanager()->height;
        des.MipLevels = 0;
        des.ArraySize = 1;
        des.Format = (DXGI_FORMAT)f;
        des.SampleDesc.Count = 1;
        des.SampleDesc.Quality = 0;
        des.Usage = (D3D11_USAGE)USAGE::DEFAULT;
        des.BindFlags = (D3D11_BIND_FLAG)bf | (D3D11_BIND_FLAG)BIND_FLAG::SHADER_RESOURCE;
        des.CPUAccessFlags = 0;
        des.MiscFlags = 0;
        
        
#endif
    }
    /*unsigned int Textura::loadCubemap(vector<std::string> faces)
    {
#ifdef openGL
        
#endif
        return 0;
    }*/
    void Textura::loadfromfile(LPCSTR f, int inverted, SRV_DIMENSION d)
    {
        TextureManager::Inst()->LoadTexture(f, inverted,this,d);
    }

    void Textura::release()
    {
#ifdef directX
        if(get!=NULL)
        get->Release();
#endif
    }
    void Textura::init()
    {
#ifdef directX
        HRESULT hr = getmanager()->getDevice()->get()->CreateTexture2D(&des, NULL, &get);
#endif
#ifdef openGL
        glGenTextures(1, &srv.get);
        glBindTexture(GL_TEXTURE_2D, srv.get);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getmanager()->width, getmanager()->height, 0, GL_RGBA, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);
#endif
    }
    void Textura::GenerateMips()
    {
        if (get) {
            CD3D11_SHADER_RESOURCE_VIEW_DESC srvd;
            ZeroMemory(&srvd, sizeof(srvd));
            srvd.ViewDimension = (D3D11_SRV_DIMENSION)SRV_DIMENSION::TEXTURE2D;
            srvd.Texture2D.MipLevels = -1;

            GraphicsModule::getmanager()->getDevice()->get()->CreateShaderResourceView(get, &srvd, &srv.get);
            getmanager()->getConext()->get()->GenerateMips(srv.get);
        }
        
    }
    void Textura::update(unsigned char*& bits, unsigned int pitch)
    {
       getmanager()->getConext()->get()->UpdateSubresource(get, 0, NULL, bits, pitch, 0);
    }
}
