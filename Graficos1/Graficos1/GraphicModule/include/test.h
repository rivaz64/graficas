#pragma once

#include <windows.h>
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
#ifdef openGL

#include<glad\glad.h>
#define GLFW_INCLUDE_NONE
#include<glfw\glfw3.h>
#include<glfw\glfw3native.h>
#include <glm/gtc/matrix_transform.hpp>
#endif
#include"manager.h"
#include"camera.h"
#include"objeto.h"
#include"VertexShader.h"
#include"InputLayout.h"
#include"PixelShader.h"
#include"SamplerState.h"
#include "chader.h"
#include<vector>
#include<string>
namespace GraphicsModule
{
  struct SimpleVertex
  {
#ifdef directX
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
    XMFLOAT3 Nor;
#endif
  };
  
  struct CBNeverChanges
  {
    float mView[16];
  };
  struct dirlight
  {
      float color[4];
      float dir[4];
  };
  struct pointlight
  {
      float color[4];
      float pos[3];
      float att;
  };
  
  struct spotlight
  {
      float Color[4];
      float Dir[4];
      float Pos[4];
      float Att;
      float Rad;
      float dif;
  };

  struct CBChangeOnResize
  {
#ifdef openGL
      glm::mat4 Projection;
#endif
      float mProjection[16];
  };

  struct CBChangesEveryFrame
  {
#ifdef directX
    XMMATRIX mWorld;
#else
      float mWorld[16];
#endif

    //float vMeshColor[4];
  };

  class test
  {
      manager* man;
      
  public:
      int chadnum=0;
      chader shad;
      std::vector<chader>chaders;
      dirlight dl;
      pointlight pl;
      spotlight sl;
      float posly[3] = { 7,7,7 };
      bool cerrar = true;
      HWND g_hwnd;
#ifdef openGL
      GLFWwindow* window;
#endif
      DRIVER_TYPE                     g_driverType = DRIVER_TYPE::DT_NULL;
      FEATURE_LEVEL                   g_featureLevel = FEATURE_LEVEL::LEVEL_11_0;
      UINT width;
      UINT heigh;
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
      

      Buffer view;
      Buffer proyection;
      Buffer translation;
      Textura texturbitco;
      Textura texturmar;
      Buffer Dirlight;
      Buffer Poslight;
      Buffer Spotlight;
      SamplerState samsta;
      static test* esta;
      objeto* fpl;
      objeto* fsl;
      //unsigned int shader;
      //glm::mat4 matrix;
#ifdef directX
      //ID3D11SamplerState* g_pSamplerLinear = NULL;
      XMMATRIX                            g_World;
      XMMATRIX                            g_View;
      XMMATRIX                            g_Projection;
      XMFLOAT4                            g_vMeshColor;

      //ID3D11RasterizerState* g_Rasterizer = NULL;
#endif
  public:
#ifdef directX
      HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
#endif
      static LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
#ifdef openGL
      static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#endif
      HRESULT InitWindow(LONG _width, LONG _height, LRESULT prochan  (HWND , UINT , WPARAM , LPARAM ) );
      HRESULT InitDevice();
      
      void rezise(HWND& _hwnd, LPARAM _lParam);
      void Update();
      void clear();
      void draw(objeto& o);
      void Render();
      void CleanupDevice();
      float f[16];
      HWND m_hwnd;
  };

}