#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include"manager.h"
#include"camera.h"
#include"objeto.h"
#include"VertexShader.h"
#include"InputLayout.h"
#include"PixelShader.h"
namespace GraphicsModule
{
  struct SimpleVertex
  {
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
    XMFLOAT3 Nor;
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
      
      float dirly[3];



      DRIVER_TYPE                     g_driverType = DRIVER_TYPE::DT_NULL;
      FEATURE_LEVEL                   g_featureLevel = FEATURE_LEVEL::LEVEL_11_0;
      
      RenderTargetView rtv;
      RenderTargetView rtv2;
      RenderTargetView rtv3;
      RenderTargetView rtv4;
      camera* cam;
      mesh cubito;
      objeto cubo;
      objeto cubo0;
      objeto cubo1;
      objeto cubo2;
      DepthStencil depstencil;
      VertexShader vrtxshdr;
      InputLayout intplyut;
      VertexShader vrtxshdr0;
      InputLayout intplyut0;
#ifdef directX
      //ID3D11VertexShader* g_pVertexShader = NULL;
      //ID3D11PixelShader* g_pPixelShader = NULL;
      PixelShader pixshad;
      //ID3D11InputLayout* g_pVertexLayout = NULL;
#endif
      Buffer neverChangesB;
      Buffer changesOnReziseB;
      Buffer changeveryFrameB;
      Textura texturbitco;
      Textura texturmar;
      Buffer Dirlight;
#ifdef directX
      ID3D11SamplerState* g_pSamplerLinear = NULL;
      XMMATRIX                            g_World;
      XMMATRIX                            g_View;
      XMMATRIX                            g_Projection;
      XMFLOAT4                            g_vMeshColor;
      
      ID3D11RasterizerState* g_Rasterizer = NULL;
#endif
  public:
#ifdef directX
      HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
#endif
      HRESULT InitDevice(HWND _hwnd);
      void rezise(HWND& _hwnd, LPARAM _lParam);
      void Update();
      void clear();
      void Render(void (*UI)());

      void CleanupDevice();

      HWND m_hwnd;
  };

}