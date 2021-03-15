#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
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
#include"PixelShader.h"
namespace GraphicsModule {
    class manager
    {
        Device dev;
        DeviceContext devcon;
        SwapChain eswap;
        //ID3D11Device* g_pd3dDevice;
        //ID3D11DeviceContext* g_pImmediateContext = NULL;
        //IDXGISwapChain* g_pSwapChain = NULL;
        HWND g_hWndM;
        DXGI_SWAP_CHAIN_DESC sd;

    public:
        CD3D11_VIEWPORT v;
        UINT width;
        UINT height;
        Device* getDevice() {
            return &dev;
        }
        DeviceContext* getConext() {
            return &devcon;
        }
        SwapChain* getSwapchain() {
            return &eswap;
        }
        HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
        void create(HWND g_hWnd);
        void descrivesch();
        HRESULT init(DRIVER_TYPE v_driverType, UINT createDeviceFlags, FEATURE_LEVEL* featureLevels, UINT numFeatureLevels, FEATURE_LEVEL g_featureLevel);
        void createrendertarget(RenderTargetView& rtv);
        void RSSetViewports(Viewport& vp);
        void draw(objeto o,  Buffer& changeveryFrameB);
        void setrenderfortextur(RenderTargetView& rtv);
        HRESULT compileVS(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,VertexShader& vs ,InputLayout& il);
        HRESULT compilePX(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, PixelShader& px);
    };
    extern manager* getmanager();
}


