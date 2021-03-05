#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
namespace GraphicsModule {
    class Buffer
    {
    public:
#ifdef directX
        ID3D11Buffer* buf = NULL;
#endif // directX

    public:
#ifdef directX
        ID3D11Buffer* get() { return buf; };
#else
        void get() {  };
#endif
        ~Buffer();
    };
}

