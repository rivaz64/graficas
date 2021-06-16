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
		rtv.textur[0] = pBackBuffer;
		dev.CreateRenderTargetView(rtv,false,1);
		//pBackBuffer.release();
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



	void manager::draw(objeto* o, Buffer* changeveryFrameB, chader& chad)
	{
#ifdef openGL
		glActiveTexture(GL_TEXTURE0);
		
		glm::mat4 Model = glm::mat4(1.0f);
		float rotate = o->rot[0]+ o->rot[1]+ o->rot[2];
		Model = glm::translate(Model, glm::vec3(o->posi[0], o->posi[1], o->posi[2]));
		Model = glm::scale(Model, glm::vec3(o->size[0], o->size[1], o->size[2]));
		if(o->rot[0]!=0)
			Model = glm::rotate(Model, float(o->rot[0] / 180.f * PI), glm::vec3(1, 0,0));
		if (o->rot[1] != 0)
			Model = glm::rotate(Model, float(o->rot[1] / 180.f * PI), glm::vec3(0,1, 0));
		if (o->rot[2] != 0)
			Model = glm::rotate(Model, float(o->rot[2] / 180.f * PI), glm::vec3(0,0,1));
		
		
		GLuint worldID = glGetUniformLocation(chad.shader, "world");
		glUniformMatrix4fv(worldID, 1, GL_FALSE, glm::value_ptr(Model));
		if (o->material.size() >= 1) {
			for (int i = 0; i < o->material.size(); i++) {
				glActiveTexture(GL_TEXTURE0+i);
				glBindTexture(o->material[i]->format, o->material[i]->get);
			}
		}
#endif
#ifdef directX
		getmanager()->getConext()->IASetPrimitiveTopology(PRIMITIVE_TOPOLOGY::TRIANGLELIST);
		XMMATRIX g_World;
		CBChangesEveryFrame cb;
		
		g_World = XMMatrixMultiply(XMMatrixScaling(o->size[0], o->size[1], o->size[2]), XMMatrixTranslation(o->posi[0], o->posi[1], o->posi[2]));
		g_World = XMMatrixMultiply(XMMatrixRotationRollPitchYaw(o->rot[0]/180.f*PI, o->rot[1] / 180.f * PI, o->rot[2] / 180.f * PI), g_World);
		cb.mWorld = XMMatrixTranspose(g_World);
		if (changeveryFrameB != NULL) {
			devcon.UpdateSubresource(*changeveryFrameB, &cb);
		}
		
#endif
		for (int m = 0; m < o->material.size(); m++) {
			devcon.PSSetShaderResources(o->material[m], m);
		}
		for (mesh* mo : (o->mod->modelo)) {
#ifdef openGL
			glBindVertexArray(mo->vao);
			glDrawElements((GLenum)PRIMITIVE_TOPOLOGY::TRIANGLELIST, mo->indexnum, GL_UNSIGNED_INT, 0);
#endif
#ifdef directX
			/*for (int m = 0; m < mo->material.size(); m++) {
				devcon.PSSetShaderResources(mo->material[m], m);
			}*/
			devcon.IASetVertexBuffers(mo->getvertex());
			devcon.IASetIndexBuffer(mo->getindices());
			devcon.draw(mo->indexnum);
#endif
		}

	}

	void manager::setrenderfortextur(RenderTargetView& rtv)
	{
#ifdef  directX
		/*rtv.release();
		rtv.textur.release();
		rtv.textur.describe(FORMAT::R8G8B8A8_UNORM, BIND_FLAG::RENDER_TARGET);
		dev.CreateTexture2D(rtv.textur);
		rtv.Format = FORMAT::R8G8B8A8_UNORM;
		rtv.ViewDimension = DIMENSION::TEXTURE2DARRAY;
		rtv.MostDetailedMip = 0;
		rtv.MipLevels = 1;
		dev.CreateShaderResourceView(rtv);
		dev.CreateRenderTargetView(rtv,false);*/
#endif
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

