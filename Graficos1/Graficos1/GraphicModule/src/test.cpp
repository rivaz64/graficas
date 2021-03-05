#include "test.h"


namespace GraphicsModule
{
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
      m_hwnd = _hwnd;
      man = getmanager();
      man->create(_hwnd);
      HRESULT hr = S_OK;

      RECT rc;
      GetClientRect(m_hwnd, &rc);
      UINT width = rc.right - rc.left;
      UINT height = rc.bottom - rc.top;

      UINT createDeviceFlags = 0;
#ifdef _DEBUG
      createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

      DRIVER_TYPE driverTypes[] =
      {
          DRIVER_TYPE::DT_HARDWARE,
           DRIVER_TYPE::DT_WARP,
           DRIVER_TYPE::DT_REFERENCE,
      };
      UINT numDriverTypes = ARRAYSIZE(driverTypes);

      FEATURE_LEVEL featureLevels[] =
      {
          FEATURE_LEVEL::LEVEL_11_0,
          FEATURE_LEVEL::LEVEL_10_1,
          FEATURE_LEVEL::LEVEL_10_0,
      };
      UINT numFeatureLevels = ARRAYSIZE(featureLevels);
      man->descrivesch();


      for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
      {
          g_driverType = driverTypes[driverTypeIndex];
          /*hr = D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)g_driverType, NULL, createDeviceFlags, (D3D_FEATURE_LEVEL*)featureLevels, numFeatureLevels,
              D3D11_SDK_VERSION, &v_swapchain.sd, &g_pSwapChain, &g_pd3dDevice, (D3D_FEATURE_LEVEL*)(&g_featureLevel), &g_pImmediateContext);
          if (SUCCEEDED(hr))*/
          hr = man->init(g_driverType, createDeviceFlags, featureLevels, numFeatureLevels, g_featureLevel);
          break;
      }
      if (FAILED(hr))
          return hr;
      //RenderTargetView rtv;
      
      man->createrendertarget(rtv);



      if (FAILED(hr))
          return hr;
      // Create depth stencil texture
      depstencil.descrivetextur();
      man->getDevice()->CreateTexture2D(depstencil.textur);


      // Create the depth stencil view
      depstencil.describeview();
      man->getDevice()->CreateDepthStencilView(depstencil);



      man->getConext()->OMSetRenderTargets(rtv, depstencil);
      //g_pDepthStencilView = depstencil.view;
      //g_pDepthStencil = depstencil.textur.get;
      //Setup the viewport
      
      Viewport vp;
      vp.Width = (FLOAT)width;
      vp.Height = (FLOAT)height;
      vp.MinDepth = 0.0f;
      vp.MaxDepth = 1.0f;
      vp.TopLeftX = 0;
      vp.TopLeftY = 0;
      //man->getConext()->RSSetViewports(vp);
      man->RSSetViewports(vp);

      // Compile the vertex shader
      ID3DBlob* pVSBlob = NULL;
      hr = CompileShaderFromFile("Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
      if (FAILED(hr))
      {
          MessageBox(NULL,
              "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
          return hr;
      }

#ifdef directX
      hr = man->getDevice()->CreateVertexShader(pVSBlob, &g_pVertexShader);
#endif
      if (FAILED(hr))
      {
          pVSBlob->Release();
          return hr;
      }

      // Define the input layout
      D3D11_INPUT_ELEMENT_DESC layout[] =
      {
          { "POSITION", 0, (DXGI_FORMAT)FORMAT::R32G32B32_FLOAT, 0, 0, (D3D11_INPUT_CLASSIFICATION)INPUT_C::VERTEX_DATA, 0 },
          { "TEXCOORD", 0, (DXGI_FORMAT)FORMAT::R32G32B32_FLOAT, 0, 12, (D3D11_INPUT_CLASSIFICATION)INPUT_C::VERTEX_DATA, 0 },
      };
      UINT numElements = ARRAYSIZE(layout);

      // Create the input layout
#ifdef directX
      hr = man->getDevice()->get()->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
          pVSBlob->GetBufferSize(), &g_pVertexLayout);
#endif
      pVSBlob->Release();
      if (FAILED(hr))
          return hr;

      // Compile the vertex shader
      ID3DBlob* pVSBlob2 = NULL;
      hr = CompileShaderFromFile("Limpio.fx", "VS", "vs_4_0", &pVSBlob2);
      if (FAILED(hr))
      {
          MessageBox(NULL,
              "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
          return hr;
      }

      // Create the vertex shader
#ifdef directX
      hr = man->getDevice()->CreateVertexShader(pVSBlob2, &g_pVertexShader2);
#endif
      if (FAILED(hr))
      {
          pVSBlob2->Release();
          return hr;
      }

      // Define the input layout
      D3D11_INPUT_ELEMENT_DESC layout2[] =
      {
          { "POSITION", 0, (DXGI_FORMAT)FORMAT::R32G32B32_FLOAT, 0, 0, (D3D11_INPUT_CLASSIFICATION)INPUT_C::VERTEX_DATA, 0 },
          { "TEXCOORD", 0, (DXGI_FORMAT)FORMAT::R32G32B32_FLOAT, 0, 12, (D3D11_INPUT_CLASSIFICATION)INPUT_C::VERTEX_DATA, 0 }
      };
      UINT numElements2 = ARRAYSIZE(layout2);

      // Create the input layout
#ifdef directX
      hr = man->getDevice()->get()->CreateInputLayout(layout2, numElements2, pVSBlob2->GetBufferPointer(),

          pVSBlob2->GetBufferSize(), &g_pVertexLayout2);
#endif
      pVSBlob2->Release();
      if (FAILED(hr))
          return hr;

      // Compile the pixel shader
      ID3DBlob* pPSBlob = NULL;
      hr = CompileShaderFromFile("Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
      if (FAILED(hr))
      {
          MessageBox(NULL,
              "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
          return hr;
      }

      // Create the pixel shader
#ifdef directX
      hr = man->getDevice()->CreatePixelShader(pPSBlob, &g_pPixelShader);
#endif
      pPSBlob->Release();
      if (FAILED(hr))
          return hr;

      // Compile the pixel shader
      ID3DBlob* pPSBlob2 = NULL;
      hr = CompileShaderFromFile("Limpio.fx", "PS", "ps_4_0", &pPSBlob2);
      if (FAILED(hr))
      {
          MessageBox(NULL,
              "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
          return hr;
      }

      // Create the pixel shader
#ifdef directX
      hr = man->getDevice()->CreatePixelShader(pPSBlob2, &g_pPixelShader2);
#endif
      pPSBlob2->Release();
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
     

      cam = new camera;
      cam->seteye(0.0f, 3.0f, -6.0f);
      cam->setat(0.0f, 1.f, 0);
      cam->setup(0.0f, 1.0f, 0);
      cam->axis();
      texturbitco.loadfromfile("bitco.dds");
      texturmar.loadfromfile("seafloor.dds");
      cubo.m = &cubito;
      cubo.tx = &texturbitco;
      cubo.posi = vector3(0, 0, 0);
      cubo0.m = &cubito;
      cubo0.tx = &texturmar;
      cubo0.posi = vector3(3, 0, 0);
      cubo1.m = &cubito;
      //cubo0.tx = &texturmar;
      cubo1.posi = vector3(-3, 0, 0);
      cubo2.m = &cubito;
      //cubo0.tx = &texturmar;
      cubo2.posi = vector3(0, 3, 0);
      // Set primitive topology
      man->getConext()->IASetPrimitiveTopology(PRIMITIVE_TOPOLOGY::TRIANGLELIST);
      D3D11_BUFFER_DESC bd;
      D3D11_SUBRESOURCE_DATA InitData;
      ZeroMemory(&bd, sizeof(bd));
      // Create the constant buffers
      bd.Usage = (D3D11_USAGE)USAGE::DEFAULT;;
      bd.ByteWidth = sizeof(CBNeverChanges);
      bd.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::CONSTANT_BUFFER;
      bd.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(bd,  neverChangesB);
      if (FAILED(hr))
          return hr;

      bd.ByteWidth = sizeof(CBChangeOnResize);
      man->getDevice()->CreateBuffer(bd, changesOnReziseB);
      if (FAILED(hr))
          return hr;

      bd.ByteWidth = sizeof(CBChangesEveryFrame);
      man->getDevice()->CreateBuffer(bd, changeveryFrameB);
      if (FAILED(hr))
          return hr;

      // Load the Texture
      
      //hr = D3DX11CreateShaderResourceViewFromFile(man->getDevice()->g_pd3dDevice, "seafloor.dds", NULL, NULL, &texturmar, NULL);

      if (FAILED(hr))
          return hr;

      // Create the sample state
#ifdef directX
      D3D11_SAMPLER_DESC sampDesc;
      ZeroMemory(&sampDesc, sizeof(sampDesc));
      sampDesc.Filter = (D3D11_FILTER)FILTER::COMPARISON_MIN_MAG_MIP_LINEAR;
      sampDesc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
      sampDesc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
      sampDesc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
      sampDesc.ComparisonFunc = (D3D11_COMPARISON_FUNC)COMPARISON_FUNC::NEVER;
      sampDesc.MinLOD = 0;
      sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
      hr = hr = man->getDevice()->get()->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
#endif
      if (FAILED(hr))
          return hr;

      // Initialize the world matrices
      g_World = XMMatrixIdentity();

      // Initialize the view matrix
      XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
      XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
      XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
      g_View = XMMatrixLookAtLH(Eye, At, Up);

      CBNeverChanges cbNeverChanges;
      cbNeverChanges.mView = XMMatrixTranspose(cam->getview());

      man->getConext()->UpdateSubresource(neverChangesB, &cbNeverChanges);

      // Initialize the projection matrix
      g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);

      CBChangeOnResize cbChangesOnResize;
      cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
      man->getConext()->UpdateSubresource(changesOnReziseB,&cbChangesOnResize);


      // create rasterizer state
#ifdef directX
      D3D11_RASTERIZER_DESC desc;
      ZeroMemory(&desc, sizeof(desc));
      desc.CullMode = D3D11_CULL_BACK;
      desc.FillMode = D3D11_FILL_SOLID;
      hr = hr = man->getDevice()->get()->CreateRasterizerState(&desc, &g_Rasterizer);
      if (FAILED(hr))
          return hr;

      desc.CullMode = D3D11_CULL_NONE;
      hr = hr = man->getDevice()->get()->CreateRasterizerState(&desc, &g_Rasterizer2);
      if (FAILED(hr))
          return hr;
#endif
      //Para ka textura nueva
      rtv2.textur.describe(FORMAT::R8G8B8A8_UNORM, BIND_FLAG::RENDER_TARGET);
      man->getDevice()->CreateTexture2D(rtv2.textur);
      rtv3.textur.describe(FORMAT::R8G8B8A8_UNORM, BIND_FLAG::RENDER_TARGET);
      man->getDevice()->CreateTexture2D(rtv3.textur);
      rtv4.textur.describe(FORMAT::R8G8B8A8_UNORM, BIND_FLAG::RENDER_TARGET);
      man->getDevice()->CreateTexture2D(rtv4.textur);
      if (FAILED(hr))
          return hr;

      // create the rt Shader resource view
      D3D11_SHADER_RESOURCE_VIEW_DESC descViewRT;
      ZeroMemory(&descViewRT, sizeof(descViewRT));
      descViewRT.Format = (DXGI_FORMAT)FORMAT::R8G8B8A8_UNORM;
      //si algo sale mal revisar esta flag v
      descViewRT.ViewDimension = (D3D_SRV_DIMENSION)DIMENSION::TEXTURE2DARRAY;
      descViewRT.Texture2D.MostDetailedMip = 0;
      descViewRT.Texture2D.MipLevels = 1;
      man->getDevice()->CreateShaderResourceView(rtv2, descViewRT);
      man->getDevice()->CreateShaderResourceView(rtv3, descViewRT);
      man->getDevice()->CreateShaderResourceView(rtv4, descViewRT);
      //man->getDevice()->g_pd3dDevice->CreateShaderResourceView(rtv2.textur.get, &descViewRT, &rtv2.srv);
      //CBNeverChanges cbNeverChanges;
      man->getDevice()->CreateRenderTargetView(rtv2);
      man->getDevice()->CreateRenderTargetView(rtv3);
      man->getDevice()->CreateRenderTargetView(rtv4);
      cubo1.tx = new Textura;
      cubo2.tx = new Textura;
      /*rtv.setClearColor({ 0.0f, 0.125f, 0.3f, 1.0f });
      rtv2.setClearColor({ 0.0f, 0.125f, 0.3f, 1.0f });
      rtv3.setClearColor({ 0.0f, 0.125f, 0.3f, 1.0f });
      rtv4.setClearColor({ 0.0f, 0.125f, 0.3f, 1.0f });//*/
      return S_OK;
  }
  void test::rezise(HWND& _hwnd, LPARAM _lParam)
  {
      man->getSwapchain()->rezise(_lParam, rtv);
      man->getConext()->resizewindow(cam, _hwnd, rtv,changesOnReziseB);
  }
  void test::Update() {
      static float t = 0.0f;
      if (g_driverType == DRIVER_TYPE::DT_REFERENCE)
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
      }
      g_World = XMMatrixRotationY(t);
      LPPOINT p = new POINT;
      if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
          GetCursorPos(p);
          cam->gira(p);
          CBNeverChanges cbNeverChanges;
          //man->getConext()->UpdateSubresource(cam);
          cbNeverChanges.mView = XMMatrixTranspose(cam->getview());

          man->getConext()->UpdateSubresource(neverChangesB, &cbNeverChanges);
      }
      else {
          cam->click = false;
      }
      delete p;
      // Modify the color
      cubo.color.x = .9;
      cubo.color.y =.9;
      cubo.color.z =.9;
      cubo0.color.x = .9;
      cubo0.color.y = .9;
      cubo0.color.z = .9;
      cubo1.color.x = .9;
      cubo1.color.y = .9;
      cubo1.color.z = .9;
      cubo2.color.x = .9;
      cubo2.color.y = .9;
      cubo2.color.z = .9;
      if (GetKeyState('W') & 0x8000)
      {
          cam->movez(1);
      }
      if (GetKeyState('S') & 0x8000)
      {
          cam->movez(-1);
      }
      if (GetKeyState('Q') & 0x8000)
      {
          cam->movey(1);
      }
      if (GetKeyState('A') & 0x8000)
      {
          cam->movey(-1);
      }
      if (GetKeyState('X') & 0x8000)
      {
          cam->movex(1);
      }
      if (GetKeyState('Z') & 0x8000)
      {
          cam->movex(-1);
      }
      CBNeverChanges cbNeverChanges;
      //man->getConext()->UpdateSubresource(cam);
      cbNeverChanges.mView = XMMatrixTranspose(cam->getview());

      man->getConext()->UpdateSubresource(neverChangesB, &cbNeverChanges);
  }
  void test::Render(void (*UI)())
  {
    // Update our time
   
    // Rotate cube around the origin
  

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

    man->getConext()->ClearRenderTargetView(rtv);
    man->getConext()->ClearRenderTargetView(rtv2);
    man->getConext()->ClearRenderTargetView(rtv3);
    man->getConext()->ClearRenderTargetView(rtv4);
    //
    // Clear the depth buffer to 1.0 (max depth)
    //
    man->getConext()->ClearDepthStencilView(depstencil);
    //
    // Update variables that change once per frame
    //
    CBChangesEveryFrame cb;
    /*cb.mWorld = XMMatrixTranspose(g_World);
    cb.vMeshColor = g_vMeshColor;
    man->getConext()->g_pImmediateContext->UpdateSubresource(changeveryFrameB.buf, 0, NULL, &cb, 0, 0);*/


    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    //
    // Render the cube
    //
    // Set the input layout
#ifdef directX
    man->getConext()->get()->IASetInputLayout(g_pVertexLayout);
    man->getConext()->get()->RSSetState(g_Rasterizer);
    
    man->getConext()->get()->VSSetShader(g_pVertexShader, NULL, 0);
    man->getConext()->get()->VSSetConstantBuffers(0, 1, &neverChangesB.buf);
    man->getConext()->get()->VSSetConstantBuffers(1, 1, &changesOnReziseB.buf);
    man->getConext()->get()->VSSetConstantBuffers(2, 1, &changeveryFrameB.buf);
    man->getConext()->get()->PSSetShader(g_pPixelShader, NULL, 0);
    man->getConext()->get()->PSSetConstantBuffers(2, 1, &changeveryFrameB.buf);
#endif
    man->getConext()->OMSetRenderTargets( rtv2, depstencil);
    man->draw(cubo, changeveryFrameB);
    cubo0.setTexture(rtv2);
    man->getConext()->ClearDepthStencilView(depstencil);
    man->getConext()->OMSetRenderTargets(rtv3, depstencil);
    man->draw(cubo, changeveryFrameB);
    man->draw(cubo0, changeveryFrameB);
    cubo1.setTexture(rtv3);
    man->getConext()->ClearDepthStencilView(depstencil);
    man->getConext()->OMSetRenderTargets(rtv4, depstencil);
    man->draw(cubo, changeveryFrameB);
    man->draw(cubo0, changeveryFrameB);
    man->draw(cubo1, changeveryFrameB);
    cubo2.setTexture(rtv4);
    man->getConext()->ClearDepthStencilView(depstencil);
    man->getConext()->OMSetRenderTargets(rtv, depstencil);
    man->draw(cubo, changeveryFrameB);
    man->draw(cubo0, changeveryFrameB);
    man->draw(cubo1, changeveryFrameB);
    man->draw(cubo2, changeveryFrameB);
#ifdef directX
    UI();
#endif
    man->getSwapchain()->Present();
  }

  void test::CleanupDevice()
  {
    
  }
}