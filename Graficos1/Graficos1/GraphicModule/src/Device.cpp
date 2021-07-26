#include "Device.h"
#include"DeviceContext.h"
#include "SwapChain.h"
#ifdef directX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#endif
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
#ifdef directX
	void Device::createVSwithInput(ID3D11VertexShader** vs, ID3D11InputLayout** il, ID3DBlob* Blob)
	{
		g_pd3dDevice->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), NULL, vs);
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
		HRESULT hr = g_pd3dDevice->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), Blob->GetBufferPointer(), Blob->GetBufferSize(), il);

		//Free allocation shader reflection memory
		reflection->Release();
		Blob->Release();
		//return hr;

	}
#endif
	void Device::CreateRenderTargetView(RenderTargetView& rtv,bool des,int n)
	{
#ifdef openGL
		for (int i = 0; i < n; i++) {
			glGenTextures(1, &rtv.srv[i].get);
			glBindTexture(GL_TEXTURE_2D, rtv.srv[i].get);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getmanager()->width, getmanager()->height, 0, GL_RGBA, GL_FLOAT, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
#endif
#ifdef directX
		for (int i = 0; i < n; i++)
			rtv.get.push_back(NULL);
		//rtv.get = new ID3D11RenderTargetView * [n];
		if (des) {
			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
			renderTargetViewDesc.Format = (DXGI_FORMAT)rtv.Format;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetViewDesc.Texture2D.MipSlice = 0;
			//renderTargetViewDesc.
			for(int i=0;i<n;i++)
			g_pd3dDevice->CreateRenderTargetView(rtv.textur[i].get, &renderTargetViewDesc, &rtv.get[i]);
		}
		else {
			for (int i = 0; i < n; i++)
			g_pd3dDevice->CreateRenderTargetView(rtv.textur[i].get, NULL, &rtv.get[i]);
		}
		 
#endif
	}

	

	void Device::CreateDepthStencilView(DepthStencil& ds)
	{
#ifdef directX
		g_pd3dDevice->CreateDepthStencilView(ds.textur.get, &ds.des, &ds.view);
#endif
#ifdef openGL
		glGenRenderbuffers(1, &ds.get);
		glBindRenderbuffer(GL_RENDERBUFFER, ds.get);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, getmanager()->width, getmanager()->height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ds.get);
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

	void Device::CreateShaderResourceView(RenderTargetView& rtv,int n,SRV_DIMENSION d)
	{
		rtv.srv.resize(n);
#ifdef directX
		D3D11_SHADER_RESOURCE_VIEW_DESC descViewRT;
		ZeroMemory(&descViewRT, sizeof(descViewRT));
		descViewRT.Format = (DXGI_FORMAT)rtv.Format;
		descViewRT.ViewDimension = (D3D11_SRV_DIMENSION)d;// (D3D_SRV_DIMENSION)rtv.ViewDimension;
		descViewRT.Texture2D.MostDetailedMip = rtv.MostDetailedMip;
		descViewRT.Texture2D.MipLevels = 1;// rtv.MipLevels;
		for(int i=0;i<n;i++)
		g_pd3dDevice->CreateShaderResourceView(rtv.textur[i].get, &descViewRT, &rtv.srv[i].get);
#endif
	}

	

	/*void Device::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT n, ID3DBlob* blob, InputLayout& il)
	{
#ifdef directX
		g_pd3dDevice->CreateInputLayout(desc, n, blob->GetBufferPointer(),
			blob->GetBufferSize(), &il.g_pVertexLayout);
#endif
	}*/

	void Device::CreateSamplerState(SamplerState& ss)
	{
#ifdef directX
		g_pd3dDevice->CreateSamplerState(&ss.desc, &ss.get);
#endif
	}

	
	Device::~Device()
	{
#ifdef directX
		g_pd3dDevice->Release();
#endif
	}

}

