#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include"Device.h"
#include"DeviceContext.h"
#include"SwapChain.h"
#include"camera.h"
#include<thread>
#include<vector>
#include<mutex>
#include<list>
#include<iostream>
namespace GraphicsModule
{
    enum driverT {
        DT_UNKNOWN = 0,
        DT_HARDWARE,
        DT_REFERENCE,
        DT_NULL,
        DT_SOFTWARE,
        DT_WARP
    };
    enum featurL {
        F_LEVEL_9_1 = 0x9100,
        F_LEVEL_9_2 = 0x9200,
        F_LEVEL_9_3 = 0x9300,
        F_LEVEL_10_0 = 0xa000,
        F_LEVEL_10_1 = 0xa100,
        F_LEVEL_11_0 = 0xb000
    };
  struct SimpleVertex
  {
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
  };

  struct CBNeverChanges
  {
    XMMATRIX mView;
  };

  struct CBChangeOnResize
  {
    XMMATRIX mProjection;
  };

  struct CBChangesEveryFrame
  {
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
  };

  class test
  {
  public:
      bool playing = true;
      bool whatcam = true;
      bool presed = false;
      std::vector<float*> instanses;
      std::mutex m;
      std::list<int> inputs;
      mesh cubito;
      camera* cam, cam1, cam2;
      ID3DBlob* pPSBlob;
    Device* v_device = NULL;
    DeviceContext* v_deviceContext = NULL;
    SwapChain* v_swapChain = NULL;
    driverT                     g_driverType;
    
    XMMATRIX                            g_World;
    XMMATRIX                            g_View;
    XMMATRIX                            g_Projection;
    XMFLOAT4                            g_vMeshColor;
    
  public:
      ID3D11Device* getdevice();
      ID3D11DeviceContext* getcontext();
    HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

    HRESULT InitDevice(HWND _hwnd);
    void Updeate();
    void Render(void(*UI)());

    void CleanupDevice();

    HWND m_hwnd;
    
  };
  extern test* gettestobj();
}