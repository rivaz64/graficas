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
    GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
    {
        // Crear los shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Leer el Vertex Shader desde archivo
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
        if (VertexShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();
        }
        else {
            printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
            getchar();
            return 0;
        }

        // Leer el Fragment Shader desde archivo
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
        if (FragmentShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        GLint InfoLogLength;


        // Compilar Vertex Shader
        printf("Compiling shader : %s\n", vertex_file_path);
        char const* VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
        glCompileShader(VertexShaderID);

        // Revisar Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }

        // Compilar Fragment Shader
        printf("Compiling shader : %s\n", fragment_file_path);
        char const* FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
        glCompileShader(FragmentShaderID);

        // Revisar Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }



        // Vincular el programa por medio del ID
        printf("Linking program\n");
        GLuint ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);

        // Revisar el programa
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }


        glDetachShader(ProgramID, VertexShaderID);
        glDetachShader(ProgramID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        return ProgramID;
    }
#endif
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
    /*LRESULT CALLBACK test::WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
    {
        switch (_msg)
        {
        case WM_SIZE:
#ifdef directX
            if (_wParam != SIZE_MINIMIZED && GraphicsModule::getmanager()->getSwapchain()->get()) {

                esta->rezise(_hwnd, _lParam);
            }
#endif
            return 0;
            break;

        case WM_SYSCOMMAND:
            if ((_wParam & 0xfff0) == SC_KEYMENU)
            {
                return 0;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        }
        return ::DefWindowProc(_hwnd, _msg, _wParam, _lParam);
    }
    */

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

#ifdef openGL
        shader = LoadShaders("vertexchader.txt", "pixelchader.txt");
#endif

#ifdef directX
        hr = man->compileVS("spot.fx", "VS", "vs_4_0", vrtxshdr, intplyut);
        if (FAILED(hr))
            return hr;

        man->compilePX("spot.fx", "PS", "ps_4_0", pixshad);

        if (FAILED(hr))
            return hr;

#endif
        // Create vertex buffer
  /*
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
                { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f },{0.f,0.f,1.f} },//
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
                23,20,22//
            });//*/


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
        Dirlight.ByteWidth = sizeof(float[4]);
        Dirlight.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        Dirlight.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(Dirlight);

        Poslight.Usage = USAGE::DEFAULT;
        Poslight.ByteWidth = sizeof(float[4]);
        Poslight.BindFlags = BIND_FLAG::CONSTANT_BUFFER;
        Poslight.CPUAccessFlags = 0;
        man->getDevice()->CreateBuffer(Poslight);

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
        man->shader = shader;
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
        /*if (g_driverType == DRIVER_TYPE::DT_REFERENCE)
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
        }*/
        //g_World = XMMatrixRotationY(t);
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
        // Modify the color
        /*cubo.color.x = .9;
        cubo.color.y = .9;
        cubo.color.z = .9;
        cubo0.color.x = .9;
        cubo0.color.y = .9;
        cubo0.color.z = .9;
        cubo1.color.x = .9;
        cubo1.color.y = .9;
        cubo1.color.z = .9;
        cubo2.color.x = .9;
        cubo2.color.y = .9;
        cubo2.color.z = .9;*/
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
        /*f[0] = cam->at.x;
        f[1] = cam->at.y;
        f[2] = cam->at.z;
        f[3] = 0;
        man->getConext()->UpdateSubresource(Dirlight, f);
        f[0] = cam->eye.x;
        f[1] = cam->eye.y;
        f[2] = cam->eye.z;
        f[3] = 0;
        man->getConext()->UpdateSubresource(Poslight, f);*/
        f[0] = dirly[0];
        f[1] = dirly[1];
        f[2] = dirly[2];
        f[3] = 0;
        man->getConext()->UpdateSubresource(Dirlight, f);
        f[0] = posly[0];
        f[1] = posly[1];
        f[2] = posly[2];
        f[3] = 0;
        man->getConext()->UpdateSubresource(Poslight, f);//*/

#ifdef openGL
        GLuint dirlID = glGetUniformLocation(shader, "dirlight");
        glUniform4f(dirlID, dirly[0], dirly[1], dirly[2], 0);
#endif
    }
    void test::clear()
    {
#ifdef openGL
        glClearColor(.0f, .0f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader);
        glUniform1i(glGetUniformLocation(shader, "texture1"), 0);

        GLuint viewID = glGetUniformLocation(shader, "view");
        GLuint proyectionID = glGetUniformLocation(shader, "proyection");
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
    man->getConext()->IASetInputLayout(intplyut);
/*#ifdef directX
    
    man->getConext()->get()->RSSetState(g_Rasterizer);
    
#endif*/
    man->getConext()->VSSetShader(vrtxshdr);
#ifdef directX
//luego abstraer sto
    man->getConext()->get()->VSSetConstantBuffers(0, 1, &view.buf);
    man->getConext()->get()->VSSetConstantBuffers(1, 1, &proyection.buf);
    man->getConext()->get()->VSSetConstantBuffers(2, 1, &translation.buf);
    man->getConext()->get()->VSSetConstantBuffers(3, 1, &Dirlight.buf);
    man->getConext()->get()->VSSetConstantBuffers(4, 1, &Poslight.buf);
    //aki akaba lode abstraer luego
    man->getConext()->get()->PSSetShader(pixshad.get(), NULL, 0);
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