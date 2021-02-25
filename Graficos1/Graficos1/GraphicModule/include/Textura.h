#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
class Textura
{
public:
    ID3D11Texture2D* deptstencil;
    ~Textura();
};

