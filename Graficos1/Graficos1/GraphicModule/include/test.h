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
#include"SamplerState.h"
#include "chader.h"
#include<vector>
#include<string>
#include"renderer.h"
#include"Pass.h"
#include"effecto.h"
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
  struct amblight
  {
      float color[3];
      float k;
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
  struct AOC
  {
      float sampleRadius;
      float scale;
      float bias;
      float intensity;
      int sampleIterations;
  };
  struct xtras
  {
      float viewPosition[3];
      float kSpecular;
      float shinines;
      int mipmapa=0;
  };
  struct xposure
  {
      float exposure=0;
      float exponent=0;
      float brigthTreshold=0;
      int mipmap=0;
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
      //int chadnum=0;
      //int tonenum = 0;
      chader shad;
      //std::vector<chader>lightcorrection;
      //std::vector<chader>chaders;
      //std::vector<pase>pases;
      Pass paseprueba;
      Pass tonemap;
      Pass Gbuffer;
      Pass lights;
      Pass AmbientOcluccion;
      Pass Copy;
      Pass random;
      Pass skypas;
      Pass animSkeleton;
      Pass HDR;
      Pass* actual;
      xtras xtrs;
      xposure xpos;
      effecto deferred;
      effecto forward;
      effecto skeletal;
     
      vector<GraphicsModule::objeto*>* objectsToDraw;
      
      amblight al;
      dirlight dl;
      pointlight pl;
      spotlight sl;

      float specular;
      float shinines = 6.f;
      float exp = 1;
      float expo = 1;
      float posly[3] = { 7,7,7 };
      bool cerrar = true;
      AOC amoc;
      HWND g_hwnd;
      mesh pantaia;
      mesh skeleto;
#ifdef openGL
      GLFWwindow* window;
#endif
      DRIVER_TYPE                     g_driverType = DRIVER_TYPE::DT_NULL;
      FEATURE_LEVEL                   g_featureLevel = FEATURE_LEVEL::LEVEL_11_0;
      UINT width;
      UINT heigh;
      camera* cam;
      Textura screen;

      

      Buffer view;
      Buffer proyection;
      Buffer translation;
      Buffer Ambilight;
      Buffer Dirlight;
      Buffer Poslight;
      Buffer Spotlight;
      Buffer specularb;
      Buffer exposure;
      Buffer aob;
      Buffer BoneB;
      
      bool deferar=false;
      bool animskel = false;
      
      bool gbuf;
      bool lightson;
      bool sao;
      bool isky;
      
      //pase paseprueba;
      static test* esta;
      objeto* fpl;
      objeto* fsl;
      objeto* skypox;

      
      //unsigned int shader;
      //glm::mat4 matrix;
#ifdef directX
      //ID3D11SamplerState* g_pSamplerLinear = NULL;
      XMMATRIX                            g_World;
      XMMATRIX                            g_View;
      XMMATRIX                            g_Projection;

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
      void draw(vector<GraphicsModule::objeto*>& v);
      void Render();
      void CleanupDevice();
      float f[8];
      
      HWND m_hwnd;
  };

}