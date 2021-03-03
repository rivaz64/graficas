#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
namespace GraphicsModule {
    class Buffer
    {
    public:
        ID3D11Buffer* buf = NULL;
        ID3D11Buffer* get() { return buf; };
        ~Buffer();
    };
}

