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
