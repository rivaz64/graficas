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
        rtv.get = NULL;
        man->createrendertarget(rtv);



        if (FAILED(hr))
            return hr;
        // Create depth stencil texture
        depstencil.descrivetextur();
        man->CreateTexture2D(depstencil.textur);


        // Create the depth stencil view
        depstencil.describeview();
        man->CreateDepthStencilView(depstencil);



        man->OMSetRenderTargets(rtv, depstencil);
        //g_pDepthStencilView = depstencil.view;
        //g_pDepthStencil = depstencil.textur.get;
        //Setup the viewport
        CD3D11_VIEWPORT v;
        Viewport vp;
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;

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

        hr = man->getDevice()->CreateVertexShader(pVSBlob, &g_pVertexShader);
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
        hr = man->getDevice()->g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
            pVSBlob->GetBufferSize(), &g_pVertexLayout);
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
        hr = man->getDevice()->CreateVertexShader(pVSBlob2, &g_pVertexShader2);
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
        hr = man->getDevice()->g_pd3dDevice->CreateInputLayout(layout2, numElements2, pVSBlob2->GetBufferPointer(),
            pVSBlob2->GetBufferSize(), &g_pVertexLayout2);
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
        hr = man->getDevice()->CreatePixelShader(pPSBlob, &g_pPixelShader);
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
        hr = man->getDevice()->CreatePixelShader(pPSBlob2, &g_pPixelShader2);
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
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = (D3D11_USAGE)USAGE::DEFAULT;
        bd.ByteWidth = sizeof(SimpleVertex) * 24;
        bd.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = cubito.getvertex();;

        hr = man->getDevice()->g_pd3dDevice->CreateBuffer(&bd, &InitData, &vertexB.buf);
        if (FAILED(hr))
            return hr;

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

        bd.Usage = (D3D11_USAGE)USAGE::DEFAULT;
        bd.ByteWidth = sizeof(WORD) * 36;
        bd.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        InitData.pSysMem = cubito.getindices();
        hr = man->getDevice()->g_pd3dDevice->CreateBuffer(&bd, &InitData, &indexB.buf);
        if (FAILED(hr))
            return hr;

        // Create vertex buffer
        /*SimpleVertex vertices2[] =
        {
             { XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
            { XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
            { XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
            { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
        };

        D3D11_BUFFER_DESC bd2;
        ZeroMemory(&bd2, sizeof(bd2));
        bd2.Usage = D3D11_USAGE_DEFAULT;
        bd2.ByteWidth = sizeof(SimpleVertex) * 4;
        bd2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd2.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData2;
        ZeroMemory(&InitData2, sizeof(InitData2));
        InitData2.pSysMem = vertices2;
        hr = man->getDevice()->g_pd3dDevice->CreateBuffer(&bd2, &InitData2, &g_pVertexBuffer2);
        if (FAILED(hr))
            return hr;


        // Create index buffer
        // Create vertex buffer
        WORD indices2[] =
        {
            2,0,1,
            3,0,2
        };

        bd2.Usage = D3D11_USAGE_DEFAULT;
        bd2.ByteWidth = sizeof(WORD) * 6;
        bd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd2.CPUAccessFlags = 0;
        InitData2.pSysMem = indices2;
        hr = man->getDevice()->g_pd3dDevice->CreateBuffer(&bd2, &InitData2, &g_pIndexBuffer2);
        if (FAILED(hr))
            return hr;*/



            // Set primitive topology
        man->getConext()->g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // Create the constant buffers
        bd.Usage = (D3D11_USAGE)USAGE::DEFAULT;;
        bd.ByteWidth = sizeof(CBNeverChanges);
        bd.BindFlags = (D3D11_BIND_FLAG)BIND_FLAG::CONSTANT_BUFFER;
        bd.CPUAccessFlags = 0;
        hr = hr = man->getDevice()->g_pd3dDevice->CreateBuffer(&bd, NULL, &neverChangesB.buf);
        if (FAILED(hr))
            return hr;

        bd.ByteWidth = sizeof(CBChangeOnResize);
        hr = hr = man->getDevice()->g_pd3dDevice->CreateBuffer(&bd, NULL, &changesOnReziseB.buf);
        if (FAILED(hr))
            return hr;

        bd.ByteWidth = sizeof(CBChangesEveryFrame);
        hr = hr = man->getDevice()->g_pd3dDevice->CreateBuffer(&bd, NULL, &changeveryFrameB.buf);
        if (FAILED(hr))
            return hr;

        // Load the Texture
        hr = D3DX11CreateShaderResourceViewFromFile(man->getDevice()->g_pd3dDevice, "bitco.dds", NULL, NULL, &g_pTextureRV, NULL);
        if (FAILED(hr))
            return hr;

        // Create the sample state
        D3D11_SAMPLER_DESC sampDesc;
        ZeroMemory(&sampDesc, sizeof(sampDesc));
        sampDesc.Filter = (D3D11_FILTER)FILTER::COMPARISON_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
        sampDesc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
        sampDesc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)ADDRESS_MODE::WRAP;
        sampDesc.ComparisonFunc = (D3D11_COMPARISON_FUNC)COMPARISON_FUNC::NEVER;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
        hr = hr = man->getDevice()->g_pd3dDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
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
        cbNeverChanges.mView = XMMatrixTranspose(g_View);
        man->getConext()->g_pImmediateContext->UpdateSubresource(neverChangesB.buf, 0, NULL, &cbNeverChanges, 0, 0);

        // Initialize the projection matrix
        g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);

        CBChangeOnResize cbChangesOnResize;
        cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
        man->getConext()->g_pImmediateContext->UpdateSubresource(changesOnReziseB.buf, 0, NULL, &cbChangesOnResize, 0, 0);


        // create rasterizer state
        D3D11_RASTERIZER_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.CullMode = D3D11_CULL_BACK;
        desc.FillMode = D3D11_FILL_SOLID;
        hr = hr = man->getDevice()->g_pd3dDevice->CreateRasterizerState(&desc, &g_Rasterizer);
        if (FAILED(hr))
            return hr;

        desc.CullMode = D3D11_CULL_NONE;
        hr = hr = man->getDevice()->g_pd3dDevice->CreateRasterizerState(&desc, &g_Rasterizer2);
        if (FAILED(hr))
            return hr;
        //Para ka textura nueva
        rtv2.textur.describe(FORMAT::R8G8B8A8_UNORM, BIND_FLAG::RENDER_TARGET);
        man->CreateTexture2D(rtv2.textur);
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
        man->getDevice()->g_pd3dDevice->CreateShaderResourceView(rtv2.textur.get, &descViewRT,& rtv2.srv);

        man->CreateRenderTargetView(rtv2);
        return S_OK;
    }

    void test::Render()
    {
        // Update our time
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

        // Rotate cube around the origin
        g_World = XMMatrixRotationY(t);

        // Modify the color
        g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
        g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
        g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

        //
        // Clear the back buffer
        //
        float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
        man->getConext()->g_pImmediateContext->ClearRenderTargetView(rtv2.get, ClearColor);

        //
        // Clear the depth buffer to 1.0 (max depth)
        //
        man->getConext()->g_pImmediateContext->ClearDepthStencilView(depstencil.view, D3D11_CLEAR_DEPTH, 1.0f, 0);

        //
        // Update variables that change once per frame
        //
        CBChangesEveryFrame cb;
        cb.mWorld = XMMatrixTranspose(g_World);
        cb.vMeshColor = g_vMeshColor;
        man->getConext()->g_pImmediateContext->UpdateSubresource(changeveryFrameB.buf, 0, NULL, &cb, 0, 0);


        UINT stride = sizeof(SimpleVertex);
        UINT offset = 0;

        //
        // Render the cube
        //
        // Set the input layout
         man->getConext()->g_pImmediateContext->IASetInputLayout(g_pVertexLayout);
         man->getConext()->g_pImmediateContext->RSSetState(g_Rasterizer);
         man->getConext()->g_pImmediateContext->IASetVertexBuffers(0, 1, &vertexB.buf, &stride, &offset);
         man->getConext()->g_pImmediateContext->IASetIndexBuffer(indexB.buf, DXGI_FORMAT_R16_UINT, 0);
         man->getConext()->g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
         man->getConext()->g_pImmediateContext->VSSetConstantBuffers(0, 1, &neverChangesB.buf);
         man->getConext()->g_pImmediateContext->VSSetConstantBuffers(1, 1, &changesOnReziseB.buf);
         man->getConext()->g_pImmediateContext->VSSetConstantBuffers(2, 1, &changeveryFrameB.buf);
         man->getConext()->g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
         man->getConext()->g_pImmediateContext->PSSetConstantBuffers(2, 1, &changeveryFrameB.buf);
         man->getConext()->g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
         man->getConext()->g_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
         man->getConext()->g_pImmediateContext->OMSetRenderTargets(1, &rtv2.get, depstencil.view);
         man->getConext()->g_pImmediateContext->DrawIndexed(36, 0, 0);
         g_World = XMMatrixTranslation(0, 0, 0);
         cb.mWorld = XMMatrixTranspose(g_World);
         cb.vMeshColor = g_vMeshColor;
         man->getConext()->g_pImmediateContext->UpdateSubresource(changeveryFrameB.buf, 0, NULL, &cb, 0, 0);
         man->getConext()->g_pImmediateContext->DrawIndexed(36, 0, 0);
         man->getConext()->g_pImmediateContext->ClearRenderTargetView(rtv.get, ClearColor);

         //
         // Clear the depth buffer to 1.0 (max depth)
         //
         man->getConext()->g_pImmediateContext->ClearDepthStencilView(depstencil.view, D3D11_CLEAR_DEPTH, 1.0f, 0);
        //
        // Render the SAQ
        //
         man->getConext()->g_pImmediateContext->OMSetRenderTargets(1, &rtv.get, depstencil.view);
         man->getConext()->g_pImmediateContext->PSSetShaderResources(0, 1, &rtv2.srv);
         man->getConext()->g_pImmediateContext->DrawIndexed(36, 0, 0);

        //g_pImmediateContext->DrawIndexed(6, 0, 0);
        //
        // Present our back buffer to our front buffer
        //

        //UIRender();
         /*for (float* i : instanses) {
             cb.mWorld = XMMatrixTranspose(i);
             g_pImmediateContext->UpdateSubresource(changeveryFrameB.buf, 0, NULL, &cb, 0, 0);
             g_pImmediateContext->DrawIndexed(36, 0, 0);
         }*/
        
         man->getSwapchain()->Present();
    }

    void test::CleanupDevice()
    {
        /*if (g_pImmediateContext) g_pImmediateContext->ClearState();

        if (g_pSamplerLinear) g_pSamplerLinear->Release();
        if (g_pTextureRV) g_pTextureRV->Release();
        if (neverChangesB.buf) neverChangesB.buf->Release();
        if (changesOnReziseB.buf) changesOnReziseB.buf->Release();
        if (changeveryFrameB.buf) changeveryFrameB.buf->Release();
        if (g_pVertexBuffer) g_pVertexBuffer->Release();
        if (g_pIndexBuffer) g_pIndexBuffer->Release();
        if (g_pVertexLayout) g_pVertexLayout->Release();
        if (g_pVertexShader) g_pVertexShader->Release();
        if (g_pPixelShader) g_pPixelShader->Release();
        if (g_pDepthStencil) g_pDepthStencil->Release();
        if (g_pDepthStencilView) g_pDepthStencilView->Release();
        if (rendertarget.get) rendertarget.get->Release();
        if (g_pSwapChain) g_pSwapChain->Release();
        if (g_pImmediateContext) g_pImmediateContext->Release();
        if (g_pd3dDevice) g_pd3dDevice->Release();*/
    }
}