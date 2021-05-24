#pragma once
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
namespace GraphicsModule {
	class shader
	{
	public:
#ifdef directX
		HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut, string tecnica);
#endif
#ifdef openGL
		GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path, string tecnica);
#endif
	};
}


