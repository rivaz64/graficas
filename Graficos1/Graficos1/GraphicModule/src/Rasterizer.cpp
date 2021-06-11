#include "Rasterizer.h"
#include "manager.h"
namespace GraphicsModule {
	void Rasterizer::create(CULING cul)
	{
		c = cul;
#ifdef directX
		
		D3D11_RASTERIZER_DESC rasdes;
		ZeroMemory(&rasdes, sizeof(rasdes));
		rasdes.CullMode = (D3D11_CULL_MODE)cul;
		rasdes.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		getmanager()->getDevice()->get()->CreateRasterizerState(&rasdes, &g_Rasterizer);
#endif
	}
	void Rasterizer::setear()
	{
#ifdef directX
		getmanager()->getConext()->get()->RSSetState(g_Rasterizer);
#endif
#ifdef openGL
		glEnable(GL_CULL_FACE);
		glCullFace((GLenum)c);
#endif
	}
}