#include "test.h"


namespace GraphicsModule
{
    HRESULT test::CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
    {
#ifdef directX
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
#endif
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
#ifdef directX
      // Compile the vertex shader
      /*ID3DBlob* pVSBlob = NULL;
      hr = CompileShaderFromFile("Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
      if (FAILED(hr))
      {
          MessageBox(NULL,
              "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
          return hr;
      }

      man->getDevice()->createVSwithInput(vrtxshdr, intplyut, pVSBlob);*/
      
      hr=man->compileVS("Tutorial07.fx", "VS", "vs_4_0", vrtxshdr, intplyut);
      if (FAILED(hr))
          return hr;

      man->compilePX("Tutorial07.fx", "PS", "ps_4_0", pixshad);
      
      if (FAILED(hr))
          return hr;

      // Compile the pixel shader
     
      // Create the pixel shader

#endif
      // Create vertex buffer

      cubito.setvertex(
          {
              { {-1.0f, 1.0f, 1.0f}, {0,0},{-1.0f, 1.0f, 1.0f} },
              { {1.0f, 1.0f, 1.0f}, {0,0},{1.0f, 1.0f, 1.0f} },
              { {-1.0f, 1.0f, -1.0f}, {0,0},{-1.0f, 1.0f, -1.0f} },
              { {1.0f, 1.0f, -1.0f}, {0,0},{1.0f, 1.0f, -1.0f}},
              { {-1.0f, -1.0f, 1.0f}, {0,0},{-1.0f, -1.0f, 1.0f} },
              { {1.0f, -1.0f, 1.0f}, {0,0},{1.0f, -1.0f, 1.0f}},
              { {-1.0f, -1.0f, -1.0f}, {0,0},{-1.0f, -1.0f, -1.0f}},
              { {1.0f, -1.0f, -1.0f}, {0,0},{1.0f, -1.0f, -1.0f} },
              /*
              { {-1.0f, 1.0f, -1.0f}, {0,0},{0.f,1.f,0.f} },
              { { 1.0f, 1.0f, -1.0f }, { 1.0f, 0.0f },{0.f,1.f,0.f} },
              { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } ,{0.f,1.f,0.f}},
              { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } ,{0.f,1.f,0.f}},

              { { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f } ,{0.f,-1.f,0.f}},
              { { 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f },{0.f,-1.f,0.f} },
              { { 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f },{0.f,-1.f,0.f} },
              { { -1.0f, -1.0f, 1.0f }, { 0.0f, 1.0f },{0.f,-1.f,0.f} },

              { { -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f },{-1.f,0.f,0.f}},
              { { -1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } ,{-1.f,0.f,0.f}},
              { { -1.0f, 1.0f, -1.0f }, { 1.0f, 1.0f },{-1.f,0.f,0.f}},
              { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } ,{-1.f,0.f,0.f}},

              { { 1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f },{1.f,0.f,0.f} },
              { { 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } ,{1.f,0.f,0.f}},
              { { 1.0f, 1.0f, -1.0f }, { 1.0f, 1.0f },{1.f,0.f,0.f} },
              { { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } ,{1.f,0.f,0.f}},

              { { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f },{0.f,0.f,-1.f}},
              { { 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f },{0.f,0.f,-1.f}},
              { { 1.0f, 1.0f, -1.0f }, { 1.0f, 1.0f },{0.f,0.f,-1.f}},
              { { -1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f } ,{0.f,0.f,-1.f}},

              { { -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f } ,{0.f,0.f,1.f}},
              { { 1.0f, -1.0f, 1.0f }, { 1.0f, 0.0f } ,{0.f,0.f,1.f}},
              { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } ,{0.f,0.f,1.f}},
              { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f },{0.f,0.f,1.f} },//*/
          });
      
      cubito.setindices(
          {
              0,1,2,
              1,3,2,
              0,4,1,
              1,4,5,
              2,4,0,
              2,6,4,
              1,7,3,
              1,5,7,
              4,6,7,
              7,5,4,
              2,7,6,
              7,2,3,
              /*
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
              23,20,22//*/
          });
     

      cam = new camera;
      cam->seteye(0.0f, 3.0f, -6.0f);
      cam->setat(0.0f, 1.f, 0);
      cam->setup(0.0f, 1.0f, 0);
      cam->axis();
      texturbitco.loadfromfile("bitco.dds");
      texturmar.loadfromfile("seafloor.dds");
      //cubo.m = &cubito;
      cubo.tx = &texturbitco;
      cubo.posi = vector3(0, 0, 0);
      //cubo0.m = &cubito;
      cubo0.tx = &texturmar;
      cubo0.posi = vector3(3, 0, 0);
      //cubo1.m = &cubito;
      //cubo0.tx = &texturmar;
      cubo1.posi = vector3(-3, 0, 0);
      //cubo2.m = &cubito;
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

      bd.ByteWidth = sizeof(float[4]);
      man->getDevice()->CreateBuffer(bd, Dirlight);

      if (FAILED(hr))
          return hr;

      // Load the Texture
      
      //hr = D3DX11CreateShaderResourceViewFromFile(man->getDevice()->g_pd3dDevice, "seafloor.dds", NULL, NULL, &texturmar, NULL);

      if (FAILED(hr))
          return hr;

      // Create the sample state
#ifdef directX
      D3D11_SAMPLER_DESC sampDesc;
      ZeroMemory(&samsta.desc, sizeof(samsta.desc));
      samsta.desc.Filter = (D3D11_FILTER)FILTER::COMPARISON_MIN_MAG_MIP_LINEAR;
      samsta.desc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
      samsta.desc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
      samsta.desc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
      samsta.desc.ComparisonFunc = (D3D11_COMPARISON_FUNC)COMPARISON_FUNC::NEVER;
      samsta.desc.MinLOD = 0;
      samsta.desc.MaxLOD = D3D11_FLOAT32_MAX;
      man->getDevice()->CreateSamplerState(samsta);
#endif
      if (FAILED(hr))
          return hr;

      // Initialize the world matrices
      //g_World = XMMatrixIdentity();

      // Initialize the view matrix
      /*XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
      XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
      XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
      g_View = XMMatrixLookAtLH(Eye, At, Up);*/

      CBNeverChanges cbNeverChanges;
      cbNeverChanges.mView = XMMatrixTranspose(cam->getview());

      man->getConext()->UpdateSubresource(neverChangesB, &cbNeverChanges);

      // Initialize the projection matrix
      //g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);

      CBChangeOnResize cbChangesOnResize;
      cbChangesOnResize.mProjection = XMMatrixTranspose(cam->getproyectionmatrixPerspective(width, width / (FLOAT)height, 0.01f, 600.0f));
      man->getConext()->UpdateSubresource(changesOnReziseB,&cbChangesOnResize);


      // create rasterizer state
/*#ifdef directX
      D3D11_RASTERIZER_DESC desc;
      ZeroMemory(&desc, sizeof(desc));
      desc.CullMode = D3D11_CULL_BACK;
      desc.FillMode = D3D11_FILL_SOLID;
      hr = hr = man->getDevice()->get()->CreateRasterizerState(&desc, &g_Rasterizer);
      if (FAILED(hr))
          return hr;

#endif//*/
      //Para ka textura nueva
      man->setrenderfortextur(rtv2);
      man->setrenderfortextur(rtv3);
      man->setrenderfortextur(rtv4);
      if (FAILED(hr))
          return hr;

      // create the rt Shader resource view
      
      
      
      cubo1.tx = new Textura;
      cubo2.tx = new Textura;
      return S_OK;
  }
  void test::rezise(HWND& _hwnd, LPARAM _lParam)
  {
      man->getSwapchain()->rezise(_lParam, rtv,true);
      
      man->getConext()->resizewindow(cam, _hwnd, rtv,changesOnReziseB);
      man->setrenderfortextur(rtv2);
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
      //g_World = XMMatrixRotationY(t);
      LPPOINT p = new POINT;
      if ((GetKeyState(VK_RBUTTON) & 0x100) != 0) {
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
      float v = 36;
      if (GetKeyState('W') & 0x8000)
      {
          cam->movez(v);
      }
      if (GetKeyState('S') & 0x8000)
      {
          cam->movez(-v);
      }
      if (GetKeyState('Q') & 0x8000)
      {
          cam->movey(v);
      }
      if (GetKeyState('A') & 0x8000)
      {
          cam->movey(-v);
      }
      if (GetKeyState('X') & 0x8000)
      {
          cam->movex(v);
      }
      if (GetKeyState('Z') & 0x8000)
      {
          cam->movex(-v);
      }
      CBNeverChanges cbNeverChanges;
      //man->getConext()->UpdateSubresource(cam);
      cbNeverChanges.mView = XMMatrixTranspose(cam->getview());

      man->getConext()->UpdateSubresource(neverChangesB, &cbNeverChanges);
      XMFLOAT4 f(dirly[0], dirly[1], dirly[2], 0);
      man->getConext()->UpdateSubresource(Dirlight, &f);
  }
  void test::clear()
  {
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
    man->getConext()->IASetInputLayout(intplyut);
/*#ifdef directX
    
    man->getConext()->get()->RSSetState(g_Rasterizer);
    
#endif*/
    man->getConext()->VSSetShader(vrtxshdr);
#ifdef directX
//luego abstraer sto
    man->getConext()->get()->VSSetConstantBuffers(0, 1, &neverChangesB.buf);
    man->getConext()->get()->VSSetConstantBuffers(1, 1, &changesOnReziseB.buf);
    man->getConext()->get()->VSSetConstantBuffers(2, 1, &changeveryFrameB.buf);
    man->getConext()->get()->VSSetConstantBuffers(3, 1, &Dirlight.buf);
    //aki akaba lode abstraer luego
    man->getConext()->get()->PSSetShader(pixshad.get(), NULL, 0);
    man->getConext()->get()->PSSetConstantBuffers(2, 1, &changeveryFrameB.buf);
#endif
  }
  void test::draw(objeto& o)
  {
      man->draw(o, changeveryFrameB);
  }
  void test::Render()
  {
    man->getSwapchain()->Present();
  }

  void test::CleanupDevice()
  {
    
  }
}