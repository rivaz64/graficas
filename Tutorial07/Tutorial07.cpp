//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#include"camera.h"
#include<thread>
#include<vector>
#include<mutex>
#include<list>
#include<iostream>
#include"mesh.h"
#include"instancia.h"
#include"Device.h"
#include"DeviceContext.h"
#include"SwapChain.h"
bool playing = true;
bool whatcam = true;
bool presed=false;
std::vector<float*> instanses;
std::mutex m;
std::list<int> inputs;
mesh cubito;
void input() {
    while (playing) {
        if (inputs.size() < 8) {
            int x=0;
            if (GetKeyState('W') & 0x8000)
            {
                x= x|0X2;
            }
            if (GetKeyState('S') & 0x8000)
            {
                x = x | 0X3;
            }
            if (GetKeyState('Q') & 0x8000)
            {
                x = x | 0X8;
            }
            if (GetKeyState('A') & 0x8000)
            {
                x = x | 0Xc;
            }
            if (GetKeyState('X') & 0x8000)
            {
                x = x | 0X20;
            }
            if (GetKeyState('Z') & 0x8000)
            {
                x = x | 0X30;
            }
            if (GetKeyState(VK_TAB) & 0x8000) {
                if (!presed) {
                    x = x | 0x80;
                    presed = true;
                }
            }
            else {
                presed = false;
            }
            if (x) {
                m.lock();
                inputs.push_back(x);
                m.unlock();
            }
            
        }
    }
    
    
}

camera* cam,cam1,cam2;
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
/*struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
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
*/

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device*                       g_pd3dDevice = NULL;
Device*                             v_device = NULL;
ID3D11DeviceContext*                g_pImmediateContext = NULL;
DeviceContext*                      v_deviceContext = NULL;
IDXGISwapChain*                     g_pSwapChain = NULL;
SwapChain*                           v_swapChain = NULL;
ID3D11RenderTargetView*             g_pRenderTargetView = NULL;
ID3D11Texture2D*                    g_pDepthStencil = NULL;
ID3D11DepthStencilView*             g_pDepthStencilView = NULL;
ID3D11VertexShader*                 g_pVertexShader = NULL;
ID3D11PixelShader*                  g_pPixelShader = NULL;
ID3D11InputLayout*                  g_pVertexLayout = NULL;
ID3D11Buffer*                       g_pVertexBuffer = NULL;
ID3D11Buffer*                       g_pIndexBuffer = NULL;
ID3D11Buffer*                       g_pCBNeverChanges = NULL;
ID3D11Buffer*                       g_pCBChangeOnResize = NULL;
ID3D11Buffer*                       g_pCBChangesEveryFrame = NULL;
ID3D11ShaderResourceView*           g_pTextureRV = NULL;
ID3D11SamplerState*                 g_pSamplerLinear = NULL;
XMMATRIX                            g_World;
XMMATRIX                            g_World1;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void update();
void Render();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    std::thread qwerty(input);
    
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
        return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        {
            update();
            Render();
        }
    }
    playing = false;
    qwerty.join();
    CleanupDevice();

    return ( int )msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow( L"TutorialWindowClass", L"Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );
    if( !g_hWnd )
        return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
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
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(g_hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = g_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    v_device = new Device;
    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        g_driverType = driverTypes[driverTypeIndex];
        //
        hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return hr;

    // Create a render target view
    v_device->
    /*ID3D11Texture2D* pBackBuffer = NULL;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);*/
    
    
    v_device = new Device;
    v_device->g_pd3dDevice = g_pd3dDevice;
    v_deviceContext = new DeviceContext;
    v_deviceContext->dev = v_device;
    v_deviceContext->g_pImmediateContext = g_pImmediateContext;
    v_swapChain->g_pSwapChain = g_pSwapChain;
    v_swapChain->GetBuffer();
    hr = v_device->CreateRenderTargetView(pBackBuffer);

    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;

    // Create depth stencil texture
    /*D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;*/
    hr = v_device->CreateTexture2D(width, height, &g_pDepthStencil);
    if (FAILED(hr))
        return hr;

    // Create the depth stencil view
    /*D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;*/
    hr = v_device->CreateDepthStencilView();
    if (FAILED(hr))
        return hr;
    v_deviceContext->OMSetRenderTargets(v_device);
    //g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

    // Setup the viewport
    /*D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pImmediateContext->RSSetViewports(1, &vp);*/
    v_deviceContext->RSSetViewports(width, height);

    // Compile the vertex shader
    ID3DBlob* pVSBlob = NULL;

    hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(NULL,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the vertex shader
    hr = v_device->CreateVertexShader(L"Tutorial07.fx", "VS", "vs_4_0");

    //hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // Define the input layout
    /*D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE(layout);*/

    // Create the input layout
    hr = v_device->CreateInputLayout();
    /*hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &g_pVertexLayout);*/

        //pVSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Set the input layout
    v_deviceContext->IASetInputLayout();
    //g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

    // Compile the pixel shader
    /*ID3DBlob* pPSBlob = NULL;
    hr = CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
    if (FAILED(hr))
    {
        MessageBox(NULL,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);*/
    hr = v_device->CreatePixelShader(L"Tutorial07.fx", "PS", "ps_4_0");
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
    /*D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = cubito.getvertex();*/
    
    //hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pVertexBuffer );
    if( FAILED( hr ) )
        return hr;

    // Set vertex buffer
    /*UINT stride = sizeof( SimpleVertex );
    UINT offset = 0;*/
    
    //g_pImmediateContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );

    // Create index buffer
    // Create vertex buffer
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
    //cubito.indices = indices;
    /*bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( WORD ) * 36;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = cubito.getindices();
    v_device->CreateBuffer();
    hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pIndexBuffer );*/
    hr = v_device->CreateBuffer(&cubito);
    v_deviceContext->IASetVertexBuffers();

    if( FAILED( hr ) )
        return hr;

    // Set index buffer
    //g_pImmediateContext->IASetIndexBuffer( g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
    v_deviceContext->IASetIndexBuffer();
    // Set primitive topology
    //g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    // Create the constant buffers
    /*bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(CBNeverChanges);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBNeverChanges );
    if( FAILED( hr ) )
        return hr;
    
    bd.ByteWidth = sizeof(CBChangeOnResize);
    hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangeOnResize );
    if( FAILED( hr ) )
        return hr;
    
    bd.ByteWidth = sizeof(CBChangesEveryFrame);
    hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangesEveryFrame );
    if( FAILED( hr ) )
        return hr;*/

    // Load the Texture
    //hr = D3DX11CreateShaderResourceViewFromFile(v_device->g_pd3dDevice, L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL );
    v_device->CreateShaderResourceViewFromFile(L"seafloor.dds");
    if( FAILED( hr ) )
        return hr;

    // Create the sample state
    /*D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = g_pd3dDevice->CreateSamplerState( &sampDesc, &g_pSamplerLinear );*/
    hr = v_device->CreateSamplerState();
    if( FAILED( hr ) )
        return hr;

    // Initialize the world matrices
    g_World = XMMatrixIdentity();
    g_World1 = XMMatrixIdentity();
    // Initialize the view matrix
    cam1.seteye(0.0f, 0, -1);
    cam1.setat(0.0f, 0.f, 0);
    cam1.setup(0.0f, 1.0f, 0);
    cam1.axis();
	cam2.seteye(0.0f, 0, -1);
	cam2.setat(0.0f, 0.f, 0);
	cam2.setup(0.0f, 1.0f, 0);
	cam2.axis();
    cam = &cam1;
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
	

    /*XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    g_View = XMMatrixLookAtLH( Eye, At, Up );*/
    
    /*CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = XMMatrixTranspose(cam->getview());
    g_pImmediateContext->UpdateSubresource( g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );*/
    v_deviceContext->UpdateSubresource(cam);
    
    g_Projection = cam1.getproyectionmatrixPerspective(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
    //g_Projection = cam.getproyectionmatrixOrtograpyc(6.4, 4.8, 0.01f, 100.0f);
    //CBChangeOnResize cbChangesOnResize;
    //cbChangesOnResize.mProjection = XMMatrixTranspose( cam->getproyectionmatrixPerspective(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f) );
    //g_pImmediateContext->UpdateSubresource( g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );
    v_deviceContext->resizewindow(cam, width, height);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
    if( g_pImmediateContext ) g_pImmediateContext->ClearState();

    if( g_pSamplerLinear ) g_pSamplerLinear->Release();
    if( g_pTextureRV ) g_pTextureRV->Release();
    if( g_pCBNeverChanges ) g_pCBNeverChanges->Release();
    if( g_pCBChangeOnResize ) g_pCBChangeOnResize->Release();
    if( g_pCBChangesEveryFrame ) g_pCBChangesEveryFrame->Release();
    if( g_pVertexBuffer ) g_pVertexBuffer->Release();
    if( g_pIndexBuffer ) g_pIndexBuffer->Release();
    if( g_pVertexLayout ) g_pVertexLayout->Release();
    if( g_pVertexShader ) g_pVertexShader->Release();
    if( g_pPixelShader ) g_pPixelShader->Release();
    if( g_pDepthStencil ) g_pDepthStencil->Release();
    if( g_pDepthStencilView ) g_pDepthStencilView->Release();
    if( g_pRenderTargetView ) g_pRenderTargetView->Release();
    if( g_pSwapChain ) g_pSwapChain->Release();
    if( g_pImmediateContext ) g_pImmediateContext->Release();
    if( g_pd3dDevice ) g_pd3dDevice->Release();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}
void update() {
    
    static float t = 0.0f;
    if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
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
            CBNeverChanges mv;
			//mv.mView = XMMatrixTranspose(cam->getview());
			g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &mv, 0, 0);

        } 
        else {
            cam->click = false;
        }
        
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
            if (GetKeyState(VK_TAB) & 0x8000){
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
				g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0);
            }
            inputs.pop_front();
            CBNeverChanges mv;
            //mv.mView = XMMatrixTranspose(cam->getview());
            
            g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &mv, 0, 0);
            
        }
        //g_World = XMMatrixRotationY(t);
        
        // Modify the color
        g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
        g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
        g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;
    }  // red, green, blue, alpha

    //
    // Update variables that change once per frame
    //
   
    
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Update our time
    

    

    //
    // Clear the back buffer
    //
   
    //
    // Render the cube
    //
    /*float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
    g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
    g_pImmediateContext->VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
    g_pImmediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
    g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
    g_pImmediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
    g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
    g_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
    CBChangesEveryFrame cb;
	//cb.vMeshColor = g_vMeshColor;
	g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);
	g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    for (float* i : instanses) {
		//cb.mWorld = XMMatrixTranspose(i);
		g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);
		g_pImmediateContext->DrawIndexed(36, 0, 0);
    }*/
    v_deviceContext->render(instanses);
    g_pSwapChain->Present(0, 0);
        
    
}
