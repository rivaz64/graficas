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
        des.MipLevels = 1;
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
    void Textura::loadfromfile(LPCSTR f, int inverted, SRV_DIMENSION d)
    {
        TextureManager::Inst()->LoadTexture(f, inverted,this,d);
#ifdef openGL
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
#ifdef directX
        //D3DX11CreateShaderResourceViewFromFile(getmanager()->getDevice()->get(), f, NULL, NULL, &srv, NULL);
#endif
    }

    void Textura::release()
    {
#ifdef directX
        if(get!=NULL)
        get->Release();
#endif
    }
#ifdef openGL
    unsigned int
#endif
#ifdef directX
        ID3D11ShaderResourceView*
#endif
        Textura::geter() {
#ifdef directX
        return srv;
#endif
#ifdef openGL
        return get;
#endif

    }


    
}
