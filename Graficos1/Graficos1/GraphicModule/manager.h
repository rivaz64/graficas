#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include"flags.h"
namespace GraphicsModule {
    class manager
    {
        ID3D11Device* g_pd3dDevice;
        ID3D11DeviceContext* g_pImmediateContext = NULL;
        IDXGISwapChain* g_pSwapChain = NULL;
        UINT width;
        UINT height;
        HWND g_hWndM;
        DXGI_SWAP_CHAIN_DESC sd;
    public:
        ID3D11Device* getDevice() {
            return g_pd3dDevice;
        }
        ID3D11DeviceContext* getConext() {
            return g_pImmediateContext;
        }
        IDXGISwapChain* getSwapchain() {
            IDXGISwapChain* g_pSwapChain;
        }
        void create(HWND g_hWnd);
        void descrivesch();
        HRESULT init(DRIVER_TYPE v_driverType, UINT createDeviceFlags, FEATURE_LEVEL* featureLevels, UINT numFeatureLevels, FEATURE_LEVEL g_featureLevel);
    };

}



