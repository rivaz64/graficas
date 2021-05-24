#include "chader.h"
#include"manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace GraphicsModule {
#ifdef directX
	HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut, string tecnica)
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
#ifdef openGL
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path, string tecnica)
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
			VertexShaderCode = "#version 400\n" + tecnica + sstr.str();
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
			FragmentShaderCode = "#version 400\n" + tecnica + sstr.str();
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

	void chader::compile(std::string file, std::string tecnique)
	{
#ifdef directX
		ID3DBlob* blob = NULL;
		HRESULT hr = CompileShaderFromFile((file + ".fx").c_str(), "VS", "vs_4_0", &blob, tecnique);
		if (FAILED(hr))
		{
			MessageBox(NULL,
				"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
			return;
		}
		getmanager()->getDevice()->createVSwithInput(&VertexShader, &il,blob);
		blob->Release();
		ID3DBlob* blo = NULL;
		hr = CompileShaderFromFile((file + ".fx").c_str(), "PS", "ps_4_0", &blo, tecnique);
		if (FAILED(hr))
		{
			MessageBox(NULL,
				"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
			return;
		}

		getmanager()->getDevice()->CreatePixelShader(blo, &PixelShader);
		blo->Release();
#endif
#ifdef openGL
		shader = LoadShaders((file + "v.txt").c_str(), (file + "p.txt").c_str(), tecnique);
		
#endif
	}
	void chader::setShader()
	{
#ifdef directX
		getmanager()->getConext()->get()->VSSetShader(VertexShader, NULL, 0);
		getmanager()->getConext()->get()->PSSetShader(PixelShader, NULL, 0);
		getmanager()->getConext()->get()->IASetInputLayout(il);
#endif
#ifdef openGL
		glUseProgram(shader);
#endif
	}
}