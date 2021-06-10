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
        man = getmanager();
        width = _width;
        man->width = _width;
        heigh = _height;
        man->height = _height;
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
        //man->wi
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
        
        //man->createrendertarget(deferedtv);
        //mainrender.init(FORMAT::UNKNOWN,FORMAT::FLOAT,false);
        //defered.init(FORMAT::R32G32B32A32_FLOAT, FORMAT::UNORM_S8_UINT,true);

        if (FAILED(hr))
            return hr;
       
        pantaia.points = new mesh::vertex[4];
#ifdef directX
        pantaia.points[0] = { -1.f,-1.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
        pantaia.points[1] = { 1.f,-1.f,0.f,1.f,1.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
        pantaia.points[2] = { -1.f,1.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
        pantaia.points[3] = { 1.f,1.f,0.f,1.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
#endif
#ifdef openGL
        pantaia.points[0] = { -1.f,-1.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
        pantaia.points[1] = { 1.f,-1.f,0.f,1.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
        pantaia.points[2] = { -1.f,1.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
        pantaia.points[3] = { 1.f,1.f,0.f,1.f,1.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };
#endif
        pantaia.indices = new unsigned int[6]{ 1,0,2,1,2,3 };
        pantaia.init(4, 6);
        man->screen = new objeto;
        man->screen->mod = new model;
        man->screen->mod->modelo = {&pantaia};
        man->saves = new objeto;
        man->saves->mod = new model;
        man->saves->mod->modelo = { &pantaia };
        for(int i=0;i<6;i++)
            man->screen->material.push_back(new Textura);
        for (int i = 0; i < 9; i++)
            man->saves->material.push_back(new Textura);
        ///screen.loadfromfile("Earth.dds", false,SRV_DIMENSION::TEXTURECUBE);
        
        Viewport vp;
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)heigh;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        //man->getConext()->RSSetViewports(vp);
        man->RSSetViewports(vp);
        paseprueba.compile("chad", {
            "#define VERTEX_LIGHT",
         "#define PIXEL_LIGHT",
         "#define NORMAL_MAP_LIGHT",
         "#define PIXEL_LIGHT\n#define PHONG",
         "#define NORMAL_MAP_LIGHT\n#define PHONG",
         "#define PIXEL_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT",
         "#define NORMAL_MAP_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT",
         "#define PIXEL_LIGHT\n#define PHONG\n#define BLINN_PHONG",
         "#define NORMAL_MAP_LIGHT\n#define PHONG\n#define BLINN_PHONG",
         "#define PIXEL_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT\n#define BLINN_PHONG",
         "#define NORMAL_MAP_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT\n#define BLINN_PHONG",
            }, false, { 0 },SRV_DIMENSION::TEXTURE2D,true);
        Gbuffer.compile("Gbuffer", {
            "#define VERTEX_LIGHT",
         "#define PIXEL_LIGHT",
         "#define NORMAL_MAP_LIGHT",
         "#define PIXEL_LIGHT\n#define PHONG",
         "#define NORMAL_MAP_LIGHT\n#define PHONG",
         "#define PIXEL_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT",
         "#define NORMAL_MAP_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT",
         "#define PIXEL_LIGHT\n#define PHONG\n#define BLINN_PHONG",
         "#define NORMAL_MAP_LIGHT\n#define PHONG\n#define BLINN_PHONG",
         "#define PIXEL_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT\n#define BLINN_PHONG",
         "#define NORMAL_MAP_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT\n#define BLINN_PHONG",
            }, false, { 0,1,2,3 }, SRV_DIMENSION::TEXTURE2D, true);
        lights.compile("lights", {
            "#define VERTEX_LIGHT",
         "#define PIXEL_LIGHT",
         "#define NORMAL_MAP_LIGHT",
         "#define PIXEL_LIGHT\n#define PHONG",
         "#define NORMAL_MAP_LIGHT\n#define PHONG",
         "#define PIXEL_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT",
         "#define NORMAL_MAP_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT",
         "#define PIXEL_LIGHT\n#define PHONG\n#define BLINN_PHONG",
         "#define NORMAL_MAP_LIGHT\n#define PHONG\n#define BLINN_PHONG",
         "#define PIXEL_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT\n#define BLINN_PHONG",
         "#define NORMAL_MAP_LIGHT\n#define PHONG\n#define SPECULAR_MAP_LIGHT\n#define BLINN_PHONG",
            }, false, { 0 }, SRV_DIMENSION::TEXTURE2D, true);
        AmbientOcluccion.compile("AO", { "" }, false, { 4 }, SRV_DIMENSION::TEXTURE2D, true);
        tonemap.compile("tonemap", {
            "#define BASIC",
         "#define REINHARD",
         "#define BURGES_DAWSON",
         "#define UNCHARTED2TONEMAP",
         "#define UNCHARTED2",
         "#define ALL",
          "#define BASIC\n#define DEFFERED",
         "#define REINHARD\n#define DEFFERED",
         "#define BURGES_DAWSON\n#define DEFFERED",
         "#define UNCHARTED2TONEMAP\n#define DEFFERED",
         "#define UNCHARTED2\n#define DEFFERED",
         "#define ALL\n#define DEFFERED",
            }, false, { 0 }, SRV_DIMENSION::TEXTURE2D,true);
        
       
        Copy.compile("copy", { "","#define DEFERED" }, true, { 0 },SRV_DIMENSION::TEXTURE2D, true);
        random.compile("randomnoise", { "" }, false, { 0 }, SRV_DIMENSION::TEXTURE2D, true);
        skypas.compile("skybox", { "" }, false, {5} ,SRV_DIMENSION::TEXTURE2D, true);
        cam = new camera;

        cam->seteye(0.0f, 3.0f, -6.0f);
        cam->setat(0.0f, 1.f, 0);
        cam->setup(0.0f, 1.0f, 0);
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

        Ambilight.Usage = USAGE::DEFAULT;
        Ambilight.ByteWidth = sizeof(float[4]);
        Ambilight.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        Ambilight.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(Ambilight);

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

        specularb.Usage = USAGE::DEFAULT;
        specularb.ByteWidth = sizeof(float[8]);
        specularb.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        specularb.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(specularb);

        exposure.Usage = USAGE::DEFAULT;
        exposure.ByteWidth = sizeof(float[4]);
        exposure.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        exposure.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(exposure);

        aob.Usage = USAGE::DEFAULT;
        aob.ByteWidth = sizeof(float[8]);
        aob.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        aob.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(aob);
        
        // Create the sample state
        paseprueba.vc.insert({ 0, &translation });
        paseprueba.vc.insert({ 1, &view });
        paseprueba.vc.insert({ 2, &proyection });
        paseprueba.vc.insert({ 3, &Dirlight });
        paseprueba.vc.insert({ 4, &Poslight });
        paseprueba.vc.insert({ 5, &Spotlight });
        paseprueba.pc.insert({ 2, &translation });
        paseprueba.pc.insert({ 3, &Dirlight });
        paseprueba.pc.insert({ 4, &Poslight });
        paseprueba.pc.insert({ 5, &Spotlight });
        paseprueba.pc.insert({ 6, &specularb });
        paseprueba.pc.insert({ 7, &Ambilight });
        Gbuffer.vc.insert({ 0, &translation });
        Gbuffer.vc.insert({ 1, &view });
        Gbuffer.vc.insert({ 2, &proyection });
        lights.pc.insert({ 0, &Dirlight });
        lights.pc.insert({ 1, &Poslight });
        lights.pc.insert({ 2, &Spotlight });
        lights.pc.insert({ 3, &specularb });
        lights.pc.insert({ 4, &Ambilight });
        AmbientOcluccion.pc.insert({ 0,&aob });
        tonemap.pc.insert({ 0,&exposure });
        skypas.vc.insert({ 0, &translation });
        skypas.vc.insert({ 1, &view });
        skypas.vc.insert({ 2, &proyection });
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
        if (FAILED(hr))
            return hr;

        // create the rt Shader resource view
        return S_OK;
    }
    void test::rezise(HWND& _hwnd, LPARAM _lParam)
    {
        //man->getSwapchain()->rezise(_lParam,mainrender.rtv, true);

        //man->getConext()->resizewindow(cam, _hwnd, mainrender.rtv, proyection);
        //man->setrenderfortextur(rtv);
    }
    void test::Update() {
        if (lightson) {
            actual = &lights;
        }
        else {
            actual = &paseprueba;
        }
#ifdef openGL
        glfwMakeContextCurrent(window);
        glfwPollEvents();
        if (glfwWindowShouldClose(window)) {
            cerrar = false;
        }
#endif
        static float t = 0.0f;
        static int ti = 0;
        if (ti > 36) {
            ti=0;
        }
        ti++;
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
        
       
        fpl->posi[0] = pl.pos[0];
        fpl->posi[1] = pl.pos[1];
        fpl->posi[2] = pl.pos[2];
        fsl->posi[0] = sl.Pos[0];
        fsl->posi[1] = sl.Pos[1];
        fsl->posi[2] = sl.Pos[2];
        f[0] = cam->eye.x;
        f[1] = cam->eye.y;
        f[2] = cam->eye.z;
        f[3] = specular;
        f[4] = shinines;
        man->getConext()->UpdateSubresource(Ambilight, &al);
        man->getConext()->UpdateSubresource(Dirlight, &dl);
        man->getConext()->UpdateSubresource(Poslight, &pl);//*/
        man->getConext()->UpdateSubresource(Spotlight, &sl);
        man->getConext()->UpdateSubresource(specularb, f);
        f[0] = exp;
        f[1] = exp+expo;
        man->getConext()->UpdateSubresource(exposure, f);
        man->getConext()->UpdateSubresource(aob, &amoc);
#ifdef openGL
        GLuint dirlID;
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "kambience");
        glUniform1f(dirlID, al.k);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "dirlight");
        glUniform4f(dirlID, dl.dir[0], dl.dir[1], dl.dir[2], 0);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "ambiencecolor");
        glUniform3f(dirlID, al.color[0], al.color[1], al.color[2]);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "dirlightcolor");
        glUniform4f(dirlID, dl.color[0], dl.color[1], dl.color[2], dl.color[3]);

        dirlID = glGetUniformLocation(chaders[chadnum].shader, "PointLightPos");
        glUniform4f(dirlID, pl.pos[0], pl.pos[1], pl.pos[2], 0);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "PointLightAttenuation");
        glUniform1f(dirlID, pl.att);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "PointColor");
        glUniform4f(dirlID, pl.color[0], pl.color[1], pl.color[2], pl.color[3]);

        dirlID = glGetUniformLocation(chaders[chadnum].shader, "coneLightPos");
        glUniform4f(dirlID, sl.Pos[0], sl.Pos[1], sl.Pos[2], 0);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "coneLightDir");
        glUniform4f(dirlID, sl.Dir[0], sl.Dir[1], sl.Dir[2], 0);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "coneLightAttenuation");
        glUniform1f(dirlID, sl.Att);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "coneLightColor");
        glUniform4f(dirlID, sl.Color[0], sl.Color[1], sl.Color[2], sl.Color[3]);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "Radious");
        glUniform1f(dirlID, sl.Rad);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "difucion");
        glUniform1f(dirlID, sl.dif);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "kspecular");
        glUniform1f(dirlID, specular);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "shinines");
        glUniform1f(dirlID, shinines);
        dirlID = glGetUniformLocation(chaders[chadnum].shader, "viewPosition");
        glUniform3f(dirlID, cam->eye.x, cam->eye.y, cam->eye.z);
#endif
    }
    void test::clear()
    {

        /*if (deferar) {
            defered.setTargets();
            defered.clearTargets();
        }
        else {
            paseprueba.ren.setTargets();
            paseprueba.ren.clearTargets();
        }*/
#ifdef openGL
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);

        
        //glUseProgram(chaders[chadnum].shader);
        chaders[chadnum].setShader();
        glUniform1i(glGetUniformLocation(chaders[chadnum].shader, "texture1"), 0);
        glUniform1i(glGetUniformLocation(chaders[chadnum].shader, "NormalMap"), 1);
        glUniform1i(glGetUniformLocation(chaders[chadnum].shader, "SpecularMap"), 2);
        GLuint viewID = glGetUniformLocation(chaders[chadnum].shader, "view");
        GLuint proyectionID = glGetUniformLocation(chaders[chadnum].shader, "proyection");
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(man->View.m));
        glUniformMatrix4fv(proyectionID, 1, GL_FALSE, glm::value_ptr(man->Projection.m));


#endif
    //man->getConext()->ClearRenderTargetView(rtv);
    
    //man->getConext()->ClearDepthStencilView(depstencil);
    //
    // Update variables that change once per frame
    //
    
    CBChangesEveryFrame cb;
    /*cb.mWorld = XMMatrixTranspose(g_World);
    cb.vMeshColor = g_vMeshColor;
    man->getConext()->g_pImmediateContext->UpdateSubresource(translation.buf, 0, NULL, &cb, 0, 0);*/


    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    
    

    //chaders[chadnum].setShader();
    //paseprueba.render();
  }
  
  void test::draw(objeto* o)
  {
      //man->draw(o, translation, paseprueba.chaders[paseprueba.chadernum]);
      
  }

  void test::draw(vector<GraphicsModule::objeto*>& v)
  {
      /*if (gbuf) {
          Gbuffer.render(v);
          if (lightson) {
              
              if (sao) {
                 
              }
              if (deferar) {
                  tonemap.render({ man->screen });
              }
          }
          Copy.render({ man->screen });
      }*/
      Pass::outn = 0;
      for (int i = 0; i < 6; i++)
          getmanager()->screen->material[i]->srv = NULL;
      lights.chadernum = Gbuffer.chadernum;
      if (deferar) {
          Gbuffer.render(v);
          lights.ren.setTargets();
          man->getConext()->PSSetShaderResources(skypox->material[0], 8);
          lights.render({ man->screen });
          AmbientOcluccion.render({ man->screen });
          tonemap.render({ man->screen });
          skypas.render({ skypox });
          Copy.render({ man->screen });
      }
      else {
          skypas.render({ skypox });

          paseprueba.render(v);
          tonemap.render({ man->screen });//*/
          //random.render({ man->screen });
          Copy.render({ man->screen });
      }
      
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