#include "test.h"

namespace GraphicsModule
{
    ID3D11Device* test::getdevice()
    {
        return (v_device->g_pd3dDevice);
    }
    ID3D11DeviceContext* test::getcontext()
    {
        return v_deviceContext->g_pImmediateContext;
    }
    HRESULT test::CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
  {
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows
    // the shaders to be optimized and to run exactly the way they will run in
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFileA(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
      dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
    if (FAILED(hr))
    {
      if (pErrorBlob != NULL)
        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
      if (pErrorBlob) pErrorBlob->Release();
      return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
  }

  HRESULT test::InitDevice(HWND _hwnd)
  {
    //m_hwnd = _hwnd;

    HRESULT hr = S_OK;
    v_device = new Device;
    v_device->create(_hwnd);
    

                         g_driverType = DT_NULL;
    featurL                   g_featureLevel = F_LEVEL_11_0;
    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    driverT driverTypes[] =
    {
        DT_HARDWARE,
        DT_WARP,
        DT_REFERENCE,
    };
    //UINT numDriverTypes = ARRAYSIZE(driverT);
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    featurL featureLevels[] =
    {
        F_LEVEL_11_0,
        F_LEVEL_10_1,
        F_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        g_driverType = driverTypes[driverTypeIndex];
        HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)g_driverType, NULL, createDeviceFlags, (D3D_FEATURE_LEVEL*)featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &v_swapChain->sd, &v_swapChain->g_pSwapChain, &v_device->g_pd3dDevice, ((D3D_FEATURE_LEVEL*)&g_featureLevel), &v_deviceContext->g_pImmediateContext);
    }
    
    v_deviceContext = new DeviceContext;
    v_swapChain = new SwapChain;
    v_device->create(_hwnd);
    v_deviceContext->dev = v_device;
    v_swapChain->dev = v_device;
    v_swapChain->GetBuffer();



    if (FAILED(hr))
        return hr;

    hr = v_device->CreateTexture2D();
    if (FAILED(hr))
        return hr;

    hr = v_device->CreateDepthStencilView();
    if (FAILED(hr))
        return hr;
    v_deviceContext->OMSetRenderTargets();

    // Compile the vertex shader
    ID3DBlob* pVSBlob = NULL;

    hr = CompileShaderFromFile("Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(NULL,
            "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
        return hr;
    }
    pVSBlob->Release();
    pVSBlob = NULL;
    // Create the vertex shader
    CompileShaderFromFile("Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
    hr = v_device->CreateVertexShader(pVSBlob);

    //hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }
    hr = v_device->CreateInputLayout();
    /*hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &g_pVertexLayout);*/

        //pVSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Set the input layout
    v_deviceContext->IASetInputLayout();
    CompileShaderFromFile("Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
    hr = v_device->CreatePixelShader(pPSBlob);
    //pPSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Create vertex buffer
    cubito.setvertex(
        {
            { {-1.0f, 1.0f, -1.0f}, {0,0} },
            { { 1.0f, 1.0f, -1.0f }, { 1.0f, 0.0f } },
            { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },
            { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

            { { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f } },
            { { 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } },
            { { 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f } },
            { { -1.0f, -1.0f, 1.0f }, { 0.0f, 1.0f } },

            { { -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f } },
            { { -1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } },
            { { -1.0f, 1.0f, -1.0f }, { 1.0f, 1.0f } },
            { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

            { { 1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f } },
            { { 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } },
            { { 1.0f, 1.0f, -1.0f }, { 1.0f, 1.0f } },
            { { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

            { { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f } },
            { { 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } },
            { { 1.0f, 1.0f, -1.0f }, { 1.0f, 1.0f } },
            { { -1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f } },

            { { -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f } },
            { { 1.0f, -1.0f, 1.0f }, { 1.0f, 0.0f } },
            { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },
            { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },
        });
    if (FAILED(hr))
        return hr;
    cubito.setindices(
        {
            3,1,0,
            2,1,3,

            6,4,5,
            7,4,6,

            11,9,8,
            10,9,11,

            14,12,13,
            15,12,14,

            19,17,16,
            18,17,19,

            22,20,21,
            23,20,22
        });
    v_device->setmesh(&cubito);
    v_device->CreateBuffers();
    v_deviceContext->IASetVertexBuffers();
    cam1.seteye(0.0f, 0, -1);
    cam1.setat(0.0f, 0.f, 0);
    cam1.setup(0.0f, 1.0f, 0);
    cam1.axis();
    cam = &cam1;
    v_deviceContext->resizewindow(cam, m_hwnd);
    if (FAILED(hr))
        return hr;

    // Set index buffer
    //g_pImmediateContext->IASetIndexBuffer( g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
    v_deviceContext->IASetIndexBuffer();
    v_device->CreateShaderResourceViewFromFile("seafloor.dds");
    if (FAILED(hr))
        return hr;

    hr = v_device->CreateSamplerState();
    if (FAILED(hr))
        return hr;

    // Initialize the world matrices
    //g_World = XMMatrixIdentity();
    //g_World1 = XMMatrixIdentity();
    // Initialize the view matrix

    cam2.seteye(0.0f, 0, -1);
    cam2.setat(0.0f, 0.f, 0);
    cam2.setup(0.0f, 1.0f, 0);
    cam2.axis();
    for (int i = 0; i < 4; i++) {
        instanses.push_back(new float[16]);
        for (int o = 0; o < 16; o++) {
            instanses[i][o] = 0;
        }
        instanses[i][0] = 1;
        instanses[i][5] = 1;
        instanses[i][10] = 1;
        instanses[i][15] = 1;
        instanses[i][14] = 5;
    }
    instanses[1][13] = 3;
    instanses[2][12] = 3;
    instanses[3][12] = -3;
    //instanses[0][3] = 5;

    v_deviceContext->UpdateSubresource(cam);

    v_deviceContext->resizewindow(cam, m_hwnd);
    return S_OK;
  }
  void test::Updeate()
  {

      static float t = 0.0f;
      if (g_driverType == DT_REFERENCE)
      {
          t += (float)XM_PI * 0.0125f;
      }
      else
      {
          static DWORD dwTimeStart = 0;
          DWORD dwTimeCur = GetTickCount();
          if (dwTimeStart == 0)
              dwTimeStart = dwTimeCur;
          t = (dwTimeCur - dwTimeStart) / 1000.0f;
          // Rotate cube around the origin
          /*LPPOINT p = new POINT;
          cam.gira(p);
          g_View = cam.getviewmatrix();
          CBNeverChanges mv;
          mv.mView = XMMatrixTranspose(g_View);
          g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &mv, 0, 0);*/

          LPPOINT p = new POINT;
          if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
              GetCursorPos(p);
              cam->gira(p);
              //CBNeverChanges mv;
              v_deviceContext->UpdateSubresource(cam);
              //mv.mView = XMMatrixTranspose(cam->getview());
              //v_deviceContext->g_pImmediateContext->UpdateSubresource(v_device->g_pCBNeverChanges, 0, NULL, &mv, 0, 0);
          }
          else {
              cam->click = false;
          }
          delete p;
          float vel = 1.f / 216.f;
          if (inputs.size() > 1) {
              int x = inputs.front();
              if (inputs.front() & 0X2) {
                  if (inputs.front() & 0X1) {
                      cam->movez(-1);
                  }
                  else {
                      cam->movez(1);
                  }
              }
              if (inputs.front() & 0X8) {
                  if (inputs.front() & 0X4) {
                      cam->movey(-1);
                  }
                  else {
                      cam->movey(1);
                  }
              }
              if (inputs.front() & 0X20) {
                  if (inputs.front() & 0X10) {
                      cam->movex(-1);
                  }
                  else {
                      cam->movex(1);
                  }
              }
              if (GetKeyState(VK_TAB) & 0x8000) {
                  if (whatcam) {
                      g_Projection = cam1.getproyectionmatrixPerspective(XM_PIDIV4, 64 / (FLOAT)48, 0.01f, 100.0f);
                      cam = &cam1;
                      whatcam = false;
                  }
                  else {
                      g_Projection = cam2.getproyectionmatrixOrtograpyc(6.4, 4.8, 0.01f, 100.0f);
                      cam = &cam2;
                      whatcam = true;
                  }

                  CBChangeOnResize cbChangesOnResize;
                  //cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
                  //g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0);
              }
              inputs.pop_front();
              CBNeverChanges mv;
              //mv.mView = XMMatrixTranspose(cam->getview());

              //g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &mv, 0, 0);

          }
          //g_World = XMMatrixRotationY(t);

          // Modify the color
          g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
          g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
          g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;
      }  // red, green, blue, alpha

  }
  void test::Render(void(* UI)()) {
      v_deviceContext->render(instanses);
      UI();
      v_swapChain->Present();
  }
  void test::CleanupDevice()
  {
    //if (g_pImmediateContext) g_pImmediateContext->ClearState();

    /*if (g_pSamplerLinear) g_pSamplerLinear->Release();
    if (g_pTextureRV) g_pTextureRV->Release();
    if (g_pCBNeverChanges) g_pCBNeverChanges->Release();
    if (g_pCBChangeOnResize) g_pCBChangeOnResize->Release();
    if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
    if (g_pVertexBuffer) g_pVertexBuffer->Release();
    if (g_pIndexBuffer) g_pIndexBuffer->Release();
    if (g_pVertexLayout) g_pVertexLayout->Release();
    if (g_pVertexShader) g_pVertexShader->Release();
    if (g_pPixelShader) g_pPixelShader->Release();
    if (g_pDepthStencil) g_pDepthStencil->Release();
    if (g_pDepthStencilView) g_pDepthStencilView->Release();
    if (g_pRenderTargetView) g_pRenderTargetView->Release();*/
    //if (g_pSwapChain) g_pSwapChain->Release();
    //if (g_pImmediateContext) g_pImmediateContext->Release();
    //if (g_pd3dDevice) g_pd3dDevice->Release();
  }
  test* gettestobj()
  {
      static test* ptest = NULL;
      return ptest;
  }
}