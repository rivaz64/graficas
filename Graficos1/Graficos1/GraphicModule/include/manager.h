#pragma once
#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#include "Device.h"
#include"DeviceContext.h"
#include"SwapChain.h"
#include"flags.h"
#include"RenderTargetView.h"
#include"Textura.h"
#include"DepthStencil.h"
#include"RenderTargetView.h"
#include"Viewport.h"
#include"Buffer.h"
#include"objeto.h"

#include "camera.h"
#include"chader.h"
namespace GraphicsModule {
    class manager
    {
        float world[16];
        Device dev;
        DeviceContext devcon;
        SwapChain eswap;
        HWND g_hWndM;
        

#ifdef directX
        DXGI_SWAP_CHAIN_DESC sd;
#endif
    public:
#ifdef directX
        CD3D11_VIEWPORT v;
#endif
        UINT width;
        UINT height;
        //unsigned int shader;
        Device* getDevice() {
            return &dev;
        }
        DeviceContext* getConext() {
            return &devcon;
        }
        SwapChain* getSwapchain() {
            return &eswap;
        }
#ifdef directX
        //HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut,string tecnica);
#endif
        
        void create(HWND g_hWnd);
        void descrivesch();
        HRESULT init(DRIVER_TYPE v_driverType, UINT createDeviceFlags, FEATURE_LEVEL* featureLevels, UINT numFeatureLevels, FEATURE_LEVEL g_featureLevel);
        void createrendertarget(RenderTargetView& rtv);
        void RSSetViewports(Viewport& vp);
        void draw(objeto &o,  Buffer& changeveryFrameB,chader& chad);
        void setrenderfortextur(RenderTargetView& rtv);
        //void compileshaders(std::string file,string tecnica);
        //HRESULT compileVS(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,VertexShader& vs ,InputLayout& il, string tecnica);
        //HRESULT compilePX(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, PixelShader& px, string tecnica);
        matrix Projection, View;
    };
    extern manager* getmanager();
}


