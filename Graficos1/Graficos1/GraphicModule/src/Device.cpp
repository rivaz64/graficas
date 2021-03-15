#include "Device.h"
#include"DeviceContext.h"
#include "SwapChain.h"
#include"test.h"
namespace GraphicsModule {
	HRESULT Device::create(HWND g_hWnd)
	{
		RECT rc;
		g_hWndM = g_hWnd;
		GetClientRect(g_hWnd, &rc);
		width = rc.right - rc.left;
		height = rc.bottom - rc.top;
		return S_OK;
	}
	void Device::createVSwithInput(VertexShader& vs, InputLayout& il, ID3DBlob* Blob)
	{
#ifdef directX
		
		g_pd3dDevice->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), NULL, &vs.g_pVertexShader);
		ID3D11ShaderReflection* reflection = NULL;
		if (FAILED(D3DReflect(Blob->GetBufferPointer(), Blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection)))
		{
			return;
		}
		D3D11_SHADER_DESC shaderDesc;
		reflection->GetDesc(&shaderDesc);
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
		for (UINT i = 0; i < shaderDesc.InputParameters; i++)
		{
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			reflection->GetInputParameterDesc(i, &paramDesc);

			// fill out input element desc
			D3D11_INPUT_ELEMENT_DESC elementDesc;
			elementDesc.SemanticName = paramDesc.SemanticName;
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;
			elementDesc.InputSlot = 0;
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDesc.InstanceDataStepRate = 0;

			// determine DXGI format
			if (paramDesc.Mask == 1)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
			}
			else if (paramDesc.Mask <= 3)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (paramDesc.Mask <= 7)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (paramDesc.Mask <= 15)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}

			//save element desc
			inputLayoutDesc.push_back(elementDesc);
		}
		// Try to create Input Layout
		HRESULT hr = g_pd3dDevice->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), Blob->GetBufferPointer(), Blob->GetBufferSize(), &il.g_pVertexLayout);

		//Free allocation shader reflection memory
		reflection->Release();
		Blob->Release();
		//return hr;
#endif
	}
	void Device::CreateRenderTargetView(RenderTargetView& rtv)
	{
#ifdef directX
		 g_pd3dDevice->CreateRenderTargetView(rtv.textur.get, NULL, &rtv.get);
#endif
	}

	void Device::CreateTexture2D(Textura& tx)
	{
#ifdef directX
		g_pd3dDevice->CreateTexture2D(&tx.des, NULL, &tx.get);
#endif
	}

	void Device::CreateDepthStencilView(DepthStencil& ds)
	{
#ifdef directX
		g_pd3dDevice->CreateDepthStencilView(ds.textur.get, &ds.des, &ds.view);
#endif
	}

	
#ifdef directX
	
	HRESULT Device::CreateVS(ID3DBlob* Blob, VertexShader& vs)
	{
		return g_pd3dDevice->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), NULL, &vs.g_pVertexShader);

	}
#endif
	/*HRESULT Device::CreateInputLayout()
	{
		g_pVertexLayout = NULL;
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);
		HRESULT r = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
			pVSBlob->GetBufferSize(), &g_pVertexLayout);
		pVSBlob->Release();
		return r;
	}//*/
#ifdef directX
	HRESULT Device::CreatePixelShader(ID3DBlob* pPSBlob, ID3D11PixelShader** pPixelShader)
	{

		HRESULT hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, pPixelShader);;
		pPSBlob->Release();
		return hr;

	}
#endif
	

	

	void Device::CreateShaderResourceViewFromFile(LPCSTR file)
	{
#ifdef directX
		D3DX11CreateShaderResourceViewFromFile(g_pd3dDevice, file, NULL, NULL, &g_pTextureRV, NULL);
#endif
	}

	void Device::CreateShaderResourceView(RenderTargetView& rtv, D3D11_SHADER_RESOURCE_VIEW_DESC des)
	{
#ifdef directX
		g_pd3dDevice->CreateShaderResourceView(rtv.textur.get, &des, &rtv.srv);
#endif
	}

	

	void Device::CreateBuffer(D3D11_BUFFER_DESC& bd, D3D11_SUBRESOURCE_DATA& InitData, Buffer& b)
	{

#ifdef directX
		 g_pd3dDevice->CreateBuffer(&bd, &InitData, &b.buf);
#endif // directX
		
	}

	void Device::CreateBuffer(D3D11_BUFFER_DESC& bd, Buffer& b)
	{
#ifdef directX
		g_pd3dDevice->CreateBuffer(&bd, NULL, &b.buf);
#endif // directX

		
	}

	void Device::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT n, ID3DBlob* blob, InputLayout& il)
	{
		g_pd3dDevice->CreateInputLayout(desc, n, blob->GetBufferPointer(),
			blob->GetBufferSize(), &il.g_pVertexLayout);
	}

	void Device::CreateSamplerState(SamplerState ss)
	{
		g_pd3dDevice->CreateSamplerState(&ss.desc, &ss.g_pSamplerLinear);
	}

	
	Device::~Device()
	{
		g_pd3dDevice->Release();
	}

}

