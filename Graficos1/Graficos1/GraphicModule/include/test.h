#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include"manager.h"
#include"camera.h"
#include"objeto.h"
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
      manager* man;
  public:
      std::vector<float*> instanses;
      DRIVER_TYPE                     g_driverType = DRIVER_TYPE::DT_NULL;
      FEATURE_LEVEL                   g_featureLevel = FEATURE_LEVEL::LEVEL_11_0;
      ID3D11Device* g_pd3dDevice = NULL;
      ID3D11DeviceContext* g_pImmediateContext = NULL;
      IDXGISwapChain* g_pSwapChain = NULL;
      ID3D11RenderTargetView* g_pRenderTargetView = NULL;
      RenderTargetView rtv;
      RenderTargetView rtv2;
      RenderTargetView rtv3;
      RenderTargetView rtv4;
      camera* cam;
      //Textura depthstencil;
      mesh cubito;
      objeto cubo;
      objeto cubo0;
      objeto cubo1;
      objeto cubo2;
      DepthStencil depstencil;
      //ID3D11Texture2D* g_pDepthStencil;
      //ID3D11DepthStencilView* g_pDepthStencilView = NULL;
      //ID3D11ShaderResourceView* g_pDepthStencilSRV = NULL;
      ID3D11ShaderResourceView* rsv2 = NULL;
      
      ID3D11VertexShader* g_pVertexShader = NULL;
      ID3D11PixelShader* g_pPixelShader = NULL;
      ID3D11InputLayout* g_pVertexLayout = NULL;
     
      Buffer neverChangesB;
      Buffer changesOnReziseB;
      Buffer changeveryFrameB;
      //ID3D11Buffer* g_pVertexBuffer = NULL;
      //ID3D11Buffer* g_pIndexBuffer = NULL;
      //ID3D11Buffer* g_pCBNeverChanges = NULL;
      //ID3D11Buffer* g_pCBChangeOnResize = NULL;
      //ID3D11Buffer* g_pCBChangesEveryFrame = NULL;
      Textura texturbitco;
      Textura texturmar;
      //ID3D11ShaderResourceView* texturbitco = NULL;
      //ID3D11ShaderResourceView* texturmar = NULL;
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
      HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

      HRESULT InitDevice(HWND _hwnd);
      void Update();
      void Render(void (*UI)());

      void CleanupDevice();

      HWND m_hwnd;
  };

}