#include "manager.h"
#include"flags.h"
#include"test.h"
#include <iostream>
#include <fstream>
#include <sstream>
#ifdef openGL
#include<glm\gtc\type_ptr.hpp>
#endif
#define PI 3.1415926535
#include<iostream>
namespace GraphicsModule {
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
#ifdef directX
	HRESULT manager::CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut, string tecnica)
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
		std::string chader;
		std::fstream file;
		file.open(szFileName); std::ostringstream sstr;
		sstr << file.rdbuf();
		chader = tecnica + sstr.str();
		file.close();
		/*hr = D3DX11CompileFromFileA(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);*/
		hr = D3DCompile(
			chader.c_str(),
			chader.length(),
			nullptr,
			nullptr,
			nullptr,
			szEntryPoint, szShaderModel,
			dwShaderFlags,
			0,
			ppBlobOut,
			&pErrorBlob);
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
#endif
	void manager::create(HWND g_hWnd) {
#ifdef directX
		RECT rc;
		g_hWndM = g_hWnd;
		GetClientRect(g_hWnd, &rc);
		width = rc.right - rc.left;
		height = rc.bottom - rc.top;
#endif
	}

	void manager::descrivesch()
	{
#ifdef directX
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = g_hWndM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
#endif
	}

	HRESULT manager::init(DRIVER_TYPE v_driverType, UINT createDeviceFlags, FEATURE_LEVEL* featureLevels, UINT numFeatureLevels, FEATURE_LEVEL g_featureLevel)
	{
#ifdef directX
		return D3D11CreateDeviceAndSwapChain(NULL, (D3D_DRIVER_TYPE)v_driverType, NULL, createDeviceFlags, (D3D_FEATURE_LEVEL*)featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &eswap.g_pSwapChain, &dev.g_pd3dDevice, (D3D_FEATURE_LEVEL*)(&g_featureLevel), &devcon.g_pImmediateContext);
#endif // directX
		return S_FALSE;

	}
	void manager::createrendertarget(RenderTargetView& rtv)
	{
		Textura pBackBuffer;
		eswap.GetBuffer(pBackBuffer);
		rtv.textur = pBackBuffer;
		dev.CreateRenderTargetView(rtv);
		pBackBuffer.release();
	}





	void manager::RSSetViewports(Viewport& vp)
	{
#ifdef directX
		v.Width = vp.Width;
		v.Height = vp.Height;
		v.MinDepth = vp.MinDepth;
		v.MaxDepth = vp.MaxDepth;
		v.TopLeftX = vp.TopLeftX;
		v.TopLeftY = vp.TopLeftY;

		devcon.g_pImmediateContext->RSSetViewports(1, &v);
#endif // directX


	}



	void manager::draw(objeto& o, Buffer& changeveryFrameB)
	{
#ifdef openGL
		glActiveTexture(GL_TEXTURE0);
		
		glm::mat4 Model = glm::mat4(1.0f);
		float rotate = o.rot[0]+ o.rot[1]+ o.rot[2];
		Model = glm::translate(Model, glm::vec3(o.posi[0], o.posi[1], o.posi[2]));
		Model = glm::scale(Model, glm::vec3(o.size[0], o.size[1], o.size[2]));
		if(o.rot[0]!=0)
			Model = glm::rotate(Model, float(o.rot[0] / 180.f * PI), glm::vec3(1, 0,0));
		if (o.rot[1] != 0)
			Model = glm::rotate(Model, float(o.rot[1] / 180.f * PI), glm::vec3(0,1, 0));
		if (o.rot[2] != 0)
			Model = glm::rotate(Model, float(o.rot[2] / 180.f * PI), glm::vec3(0,0,1));
		
		
		GLuint worldID = glGetUniformLocation(shader, "world");
		glUniformMatrix4fv(worldID, 1, GL_FALSE, glm::value_ptr(Model));
#endif
#ifdef directX
		getmanager()->getConext()->IASetPrimitiveTopology(PRIMITIVE_TOPOLOGY::TRIANGLELIST);
		XMMATRIX g_World;
		CBChangesEveryFrame cb;
		
		g_World = XMMatrixMultiply(XMMatrixScaling(o.size[0], o.size[1], o.size[2]), XMMatrixTranslation(o.posi[0], o.posi[1], o.posi[2]));
		g_World = XMMatrixMultiply(XMMatrixRotationRollPitchYaw(o.rot[0]/180.f*PI, o.rot[1] / 180.f * PI, o.rot[2] / 180.f * PI), g_World);
		cb.mWorld = XMMatrixTranspose(g_World);

		devcon.UpdateSubresource(changeveryFrameB, &cb);
#endif
		for (mesh* mo : (o.mod->modelo)) {
#ifdef openGL
			glBindTexture(GL_TEXTURE_2D, mo->tx->get);
			glBindVertexArray(mo->vao);
			glDrawElements((GLenum)PRIMITIVE_TOPOLOGY::TRIANGLELIST, mo->indexnum, GL_UNSIGNED_INT, 0);
#endif
#ifdef directX
			if (mo->tx != NULL)
				devcon.PSSetShaderResources(mo->tx);
			devcon.IASetVertexBuffers(mo->getvertex());
			devcon.IASetIndexBuffer(mo->getindices());
			devcon.draw(mo->indexnum);
#endif
		}

	}

	void manager::setrenderfortextur(RenderTargetView& rtv)
	{
#ifdef  directX
		rtv.release();
		rtv.textur.release();
		rtv.textur.describe(FORMAT::R8G8B8A8_UNORM, BIND_FLAG::RENDER_TARGET);
		dev.CreateTexture2D(rtv.textur);
		rtv.Format = FORMAT::R8G8B8A8_UNORM;
		rtv.ViewDimension = DIMENSION::TEXTURE2DARRAY;
		rtv.MostDetailedMip = 0;
		rtv.MipLevels = 1;
		dev.CreateShaderResourceView(rtv);
		dev.CreateRenderTargetView(rtv);
#endif
	}

	void manager::compileshaders(std::string file, string tecnica)
	{
#ifdef openGL
		shader = LoadShaders((file + "v.txt").c_str(), (file + "p.txt").c_str() );
#endif

#ifdef directX
		compileVS((file+".fx").c_str(), "VS", "vs_4_0", vrtxshdr, intplyut,tecnica);
		

		compilePX((file + ".fx").c_str(), "PS", "ps_4_0", pixshad, tecnica);
#endif
	}

	HRESULT manager::compileVS(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,  VertexShader& vs,InputLayout& il, string tecnica)
	{
#ifdef directX
		ID3DBlob* pVSBlob = NULL;
		HRESULT hr = CompileShaderFromFile(szFileName, szEntryPoint, szShaderModel, &pVSBlob,tecnica);
		if (FAILED(hr))
		{
			MessageBox(NULL,
				"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
			return hr;
		}
		dev.createVSwithInput(vs, il, pVSBlob);
		pVSBlob->Release();
		return hr;
#endif
		return S_OK;
	}

	HRESULT manager::compilePX(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, PixelShader& px, string tecnica)
	{
#ifdef directX
		ID3DBlob* pPSBlob = NULL;
		HRESULT hr = CompileShaderFromFile(szFileName, szEntryPoint, szShaderModel, &pPSBlob,tecnica);
		if (FAILED(hr))
		{
			MessageBox(NULL,
				"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
			return hr;
		}

		// Create the pixel shader
		ID3D11PixelShader* g_pPixelShader;
		hr = dev.CreatePixelShader(pPSBlob, &g_pPixelShader);
		px.g_pPixelShader = g_pPixelShader;
		pPSBlob->Release();
#endif
		return S_OK;
	}
	
	manager* getmanager()
	{
		static manager* man;
		if (man == NULL) {
			man = new manager;
		}
		return man;
	}

}

