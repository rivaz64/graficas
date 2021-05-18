#include "test.h"

#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#ifdef openGL
#include<glm\gtc\type_ptr.hpp>
#endif

namespace GraphicsModule
{

#ifdef openGL
    void test::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        std::cout << "aka" << std::endl;
        glViewport(0, 0, width, height);
        if (esta != NULL) {
            matrix cbNeverChanges;
            esta->cam->ratio = width / (FLOAT)height;
            esta->cam->getView(cbNeverChanges);
            esta->man->View = cbNeverChanges;
        }

    }
#endif
    test* test::esta = NULL;
    

    HRESULT test::InitWindow(LONG _width, LONG _height, LRESULT prochan(HWND, UINT, WPARAM, LPARAM) )
    {

        width = _width;
        heigh = _height;
#ifdef openGL

        window = glfwCreateWindow(_width, _height, "TutorialWindowClass", NULL, NULL);
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            return -1;
        }
        glViewport(0, 0, _width, _height);
        //glfwSwapInterval(1);
        glClearColor(.0f, .0f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        //window->monitor;
#endif
        // Register class
#ifdef directX

        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = prochan;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = nullptr;
        wcex.hIcon = nullptr;
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = "TutorialWindowClass";
        wcex.hIconSm = nullptr;
        if (!RegisterClassEx(&wcex))
        {
            return E_FAIL;
        }

        // Create window
        RECT rc = { 0, 0, _width, _height };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
        g_hwnd = CreateWindow("TutorialWindowClass", "Graficos 1", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, _width, _height, NULL, NULL, NULL, NULL);
        if (!g_hwnd)
        {
            return E_FAIL;
        }
        ShowWindow(g_hwnd, SW_SHOWNORMAL);
#endif
        return S_OK;
    }

    HRESULT test::InitDevice()
    {





        man = getmanager();

        man->create(g_hwnd);
        HRESULT hr = S_OK;



        UINT createDeviceFlags = 0;
#ifdef _DEBUG
#ifdef directX
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
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
            if (!FAILED(hr))
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
        vp.Height = (FLOAT)heigh;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        //man->getConext()->RSSetViewports(vp);
        man->RSSetViewports(vp);

        man->compileshaders("chad");


        


        cam = new camera;
/*#ifdef openGL
        cam->seteye(4.0f, 3.0f, 3.0f);
        cam->setat(0.0f, 0.f, 0);
        cam->setup(0.0f, 1.0f, 0);
#endif
#ifdef directX*/
        cam->seteye(0.0f, 3.0f, -6.0f);
        cam->setat(0.0f, 1.f, 0);
        cam->setup(0.0f, 1.0f, 0);
//#endif
        cam->axis();
        
        

        view.Usage = USAGE::DEFAULT;
        view.ByteWidth = sizeof(CBNeverChanges);
        view.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        view.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(view);

        proyection.Usage = USAGE::DEFAULT;
        proyection.ByteWidth = sizeof(CBChangeOnResize);
        proyection.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        proyection.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(proyection);

        translation.Usage = USAGE::DEFAULT;
        translation.ByteWidth = sizeof(CBChangesEveryFrame);
        translation.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        translation.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(translation);

        Dirlight.Usage = USAGE::DEFAULT;
        Dirlight.ByteWidth = sizeof(float[8]);
        Dirlight.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        Dirlight.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(Dirlight);

        Poslight.Usage = USAGE::DEFAULT;
        Poslight.ByteWidth = sizeof(float[8]);
        Poslight.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        Poslight.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(Poslight);

        Spotlight.Usage = USAGE::DEFAULT;
        Spotlight.ByteWidth = sizeof(float[16]);
        Spotlight.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        Spotlight.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(Spotlight);

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

       
        matrix cbNeverChanges;
        cam->getView(cbNeverChanges);
        man->View = cbNeverChanges;
        man->getConext()->UpdateSubresource(view, &cbNeverChanges);

        // Initialize the projection matrix
        //g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
        cam->angle = 0.785398163f;
        cam->ratio = width / (FLOAT)heigh;
        cam->nearp = 0.01f;
        cam->farp = 600.0f;
        matrix cbChangesOnResize;
        cam->getProyectionMatrixPerspective(cbChangesOnResize);
        man->Projection = cbChangesOnResize;
        //cbChangesOnResize.mProjection = cam->getProyectionMatrixPerspective(width, width / (FLOAT)height, 0.01f, 600.0f);
        man->getConext()->UpdateSubresource(proyection, &cbChangesOnResize);

 
  //Para ka textura nueva
        man->setrenderfortextur(rtv2);
        man->setrenderfortextur(rtv3);
        man->setrenderfortextur(rtv4);
        if (FAILED(hr))
            return hr;

        // create the rt Shader resource view



       
        return S_OK;
    }
    void test::rezise(HWND& _hwnd, LPARAM _lParam)
    {
        man->getSwapchain()->rezise(_lParam, rtv, true);

        man->getConext()->resizewindow(cam, _hwnd, rtv, proyection);
        man->setrenderfortextur(rtv2);
    }
    void test::Update() {
#ifdef openGL
        glfwMakeContextCurrent(window);
        glfwPollEvents();
        if (glfwWindowShouldClose(window)) {
            cerrar = false;
        }
#endif
        static float t = 0.0f;
       
        LPPOINT p = new POINT;
        if ((GetKeyState(VK_RBUTTON) & 0x100) != 0) {
            GetCursorPos(p);
            cam->gira(p);
            matrix cbNeverChanges;
            //man->getConext()->UpdateSubresource(cam);
            cam->getView(cbNeverChanges);

            man->getConext()->UpdateSubresource(view, &cbNeverChanges);
            man->View = cbNeverChanges;
        }
        else {
            if (cam != NULL)
                cam->click = false;
        }
        delete p;
        
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
        matrix cbNeverChanges;
        //man->getConext()->UpdateSubresource(cam);
        if (cam) {

            cam->getView(cbNeverChanges);
            man->View = cbNeverChanges;
            man->getConext()->UpdateSubresource(view, &cbNeverChanges);
        }
        
       
        
        man->getConext()->UpdateSubresource(Dirlight, &dl);
        man->getConext()->UpdateSubresource(Poslight, &pl);//*/
        man->getConext()->UpdateSubresource(Spotlight, &sl);

#ifdef openGL
        GLuint dirlID = glGetUniformLocation(man->shader, "dirlight");
        glUniform4f(dirlID, dl.dir[0], dl.dir[1], dl.dir[2], 0);
        dirlID = glGetUniformLocation(man->shader, "dirlightcolor");
        glUniform4f(dirlID, dl.color[0], dl.color[1], dl.color[2], dl.color[3]);

        dirlID = glGetUniformLocation(man->shader, "PointLightPos");
        glUniform4f(dirlID, pl.pos[0], pl.pos[1], pl.pos[2], 0);
        dirlID = glGetUniformLocation(man->shader, "PointLightAttenuation");
        glUniform1f(dirlID, pl.att);
        dirlID = glGetUniformLocation(man->shader, "PointColor");
        glUniform4f(dirlID, pl.color[0], pl.color[1], pl.color[2], pl.color[3]);

        dirlID = glGetUniformLocation(man->shader, "coneLightPos");
        glUniform4f(dirlID, sl.Pos[0], sl.Pos[1], sl.Pos[2], 0);
        dirlID = glGetUniformLocation(man->shader, "coneLightDir");
        glUniform4f(dirlID, sl.Dir[0], sl.Dir[1], sl.Dir[2], 0);
        dirlID = glGetUniformLocation(man->shader, "coneLightAttenuation");
        glUniform1f(dirlID, sl.Att);
        dirlID = glGetUniformLocation(man->shader, "coneLightColor");
        glUniform4f(dirlID, sl.Color[0], sl.Color[1], sl.Color[2], sl.Color[3]);
        dirlID = glGetUniformLocation(man->shader, "Radious");
        glUniform1f(dirlID, sl.Rad);
        dirlID = glGetUniformLocation(man->shader, "difucion");
        glUniform1f(dirlID, sl.dif);
        
        
#endif
    }
    void test::clear()
    {
#ifdef openGL
        glClearColor(.0f, .0f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(man->shader);
        glUniform1i(glGetUniformLocation(man->shader, "texture1"), 0);

        GLuint viewID = glGetUniformLocation(man->shader, "view");
        GLuint proyectionID = glGetUniformLocation(man->shader, "proyection");
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(man->View.m));
        glUniformMatrix4fv(proyectionID, 1, GL_FALSE, glm::value_ptr(man->Projection.m));

      
#endif
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
    man->getConext()->g_pImmediateContext->UpdateSubresource(translation.buf, 0, NULL, &cb, 0, 0);*/


    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    //
    // Render the cube
    //
    // Set the input layout
    man->getConext()->IASetInputLayout(man->intplyut);
/*#ifdef directX
    
    man->getConext()->get()->RSSetState(g_Rasterizer);
    
#endif*/
    man->getConext()->VSSetShader(man->vrtxshdr);
#ifdef directX
//luego abstraer sto
    man->getConext()->get()->VSSetConstantBuffers(0, 1, &view.buf);
    man->getConext()->get()->VSSetConstantBuffers(1, 1, &proyection.buf);
    man->getConext()->get()->VSSetConstantBuffers(2, 1, &translation.buf);
    man->getConext()->get()->VSSetConstantBuffers(3, 1, &Dirlight.buf);
    man->getConext()->get()->VSSetConstantBuffers(4, 1, &Poslight.buf);
    man->getConext()->get()->VSSetConstantBuffers(5, 1, &Spotlight.buf);
    //aki akaba lode abstraer luego
    man->getConext()->get()->PSSetShader(man->pixshad.get(), NULL, 0);
    man->getConext()->get()->PSSetConstantBuffers(2, 1, &translation.buf);
#endif
  }
  
  void test::draw(objeto& o)
  {
      man->draw(o, translation);

  }
  
  void test::Render()
  {

    man->getSwapchain()->Present();
#ifdef openGL
    glfwSwapBuffers(window);
#endif
  }

  void test::CleanupDevice()
  {
#ifdef directX
      DestroyWindow(g_hwnd);
#endif
#ifdef openGL
      glfwDestroyWindow(window);
#endif
  }
 
}