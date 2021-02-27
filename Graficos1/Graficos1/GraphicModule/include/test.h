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
    D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
    D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
    Device* v_device = NULL;
    DeviceContext* v_deviceContext = NULL;
    SwapChain* v_swapChain = NULL;
    ID3D11RenderTargetView* g_pRenderTargetView = NULL;
    ID3D11Texture2D* g_pDepthStencil = NULL;
    ID3D11DepthStencilView* g_pDepthStencilView = NULL;
    ID3D11ShaderResourceView* g_pDepthStencilSRV = NULL;
    ID3D11VertexShader* g_pVertexShader = NULL;
    ID3D11PixelShader* g_pPixelShader = NULL;
    ID3D11InputLayout* g_pVertexLayout = NULL;
    ID3D11Buffer* g_pVertexBuffer = NULL;
    ID3D11Buffer* g_pIndexBuffer = NULL;
    ID3D11Buffer* g_pCBNeverChanges = NULL;
    ID3D11Buffer* g_pCBChangeOnResize = NULL;
    ID3D11Buffer* g_pCBChangesEveryFrame = NULL;
    ID3D11ShaderResourceView* g_pTextureRV = NULL;
    ID3D11SamplerState* g_pSamplerLinear = NULL;
    XMMATRIX                            g_World;
    XMMATRIX                            g_View;
    XMMATRIX                            g_Projection;
    XMFLOAT4                            g_vMeshColor;
    ID3D11Buffer* g_pVertexBuffer2 = NULL;
    ID3D11Buffer* g_pIndexBuffer2 = NULL;
    ID3D11VertexShader* g_pVertexShader2 = NULL;
    ID3D11PixelShader* g_pPixelShader2 = NULL;
    ID3D11RasterizerState* g_Rasterizer = NULL;
    ID3D11RasterizerState* g_Rasterizer2 = NULL;
    ID3D11InputLayout* g_pVertexLayout2 = NULL;
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

}