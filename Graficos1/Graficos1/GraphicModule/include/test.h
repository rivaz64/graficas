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

    float vMeshColor[4];
  };

  class test
  {
      manager* man;
      
  public:

      float dirly[3];
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
      VertexShader vrtxshdr;
      InputLayout intplyut;
      VertexShader vrtxshdr0;
      InputLayout intplyut0;
      PixelShader pixshad;

      Buffer view;
      Buffer proyection;
      Buffer changeveryFrameB;
      Textura texturbitco;
      Textura texturmar;
      Buffer Dirlight;
      SamplerState samsta;
      static test* esta;
      unsigned int shader;
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
      HRESULT InitWindow(LONG _width, LONG _height);
      HRESULT InitDevice();
      void rezise(HWND& _hwnd, LPARAM _lParam);
      void Update();
      void clear();
      void draw(objeto& o);
      void draw(Buffer& o);
      void draw(mesh& o);
      void Render();
      void CleanupDevice();
      float f[4];
      HWND m_hwnd;
  };

}