#include "shader.h"
namespace GraphicsModule {
#ifdef directX
	HRESULT shader::CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut, string tecnica)
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
}