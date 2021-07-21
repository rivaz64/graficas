#pragma once
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#endif
#include <glm/glm.hpp>
#include "flags.h"
namespace GraphicsModule {
    class Buffer
    {
    public:
#ifdef directX
        ID3D11Buffer* buf = NULL;
#endif // directX
#ifdef openGL
        unsigned int buf = 0;
    public:
        glm::mat4 data;
#endif
    public:
        USAGE Usage;
        UINT ByteWidth;
        BIND_FLAG BindFlags;
        UINT CPUAccessFlags;
        void* Mem=NULL;

#ifdef directX
        ID3D11Buffer* get() { return buf; };
#else
        void get() {  };
#endif
    };
}

