#include "DeviceContext.h"
#include "camera.h"
#include"test.h"
#include"Viewport.h"
#ifdef openGL
#include<glm\gtc\type_ptr.hpp>
#endif
#include"Buffer.h"
namespace GraphicsModule {


	void DeviceContext::RSSetViewports(Viewport& vp)
	{
		/*v.Width = vp.Width;
		v.Height = vp.Height;
		v.MinDepth = vp.MinDepth;
		v.MaxDepth = vp.MaxDepth;
		v.TopLeftX = vp.TopLeftX;
		v.TopLeftY = vp.TopLeftY;

		devcon.g_pImmediateContext->RSSetViewports(1, &v);*/
	}



	void DeviceContext::IASetVertexBuffers(Buffer* b)
	{
		UINT stride = sizeof(mesh::vertex);
		UINT offset = 0;
#ifdef directX
		g_pImmediateContext->IASetVertexBuffers(0, 1, &(b->buf), &stride, &offset);
#endif
	}


	void DeviceContext::IASetIndexBuffer(Buffer* b)
	{
#ifdef directX
		g_pImmediateContext->IASetIndexBuffer(b->buf, (DXGI_FORMAT)FORMAT::R32_UINT, 0);
#endif
	}

	void DeviceContext::VSSetConstantBuffers(int i, Buffer* b)
	{
#ifdef directX
		g_pImmediateContext->VSSetConstantBuffers(i, 1, &b->buf);
#endif
#ifdef openGL
		GLuint ID;
		ID = glGetUniformLocation(getmanager()->actualchader, ("b" + std::to_string(i)).c_str());
		glUniformMatrix4fv(ID, 1, GL_FALSE, glm::value_ptr(b->data));
		//glUniform1f(ID, al.k);
#endif
		
	}

	void DeviceContext::PSSetConstantBuffers(int i, Buffer* b)
	{
#ifdef openGL
		GLuint ID;
		ID = glGetUniformLocation(getmanager()->actualchader, ("b" + std::to_string(i)).c_str());
		glUniformMatrix4fv(ID, 1, GL_FALSE, glm::value_ptr(b->data));
#endif
#ifdef directX
		g_pImmediateContext->PSSetConstantBuffers(i, 1, &b->buf);
#endif
	}

	

	void DeviceContext::UpdateView(camera* cam)
	{
		/*CBChangesEveryFrame cbChangesEveryFrame;
		cbChangesEveryFrame.mView = XMMatrixTranspose(cam->getview());
		g_pImmediateContext->UpdateSubresource(dev->g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);*/
	}

	void DeviceContext::resizewindow(camera* cam, HWND& g_hWnd,RenderTargetView& rtv,Buffer& chor)
	{
#ifdef directX
		g_pImmediateContext->OMSetRenderTargets(1,&rtv.get[0], NULL);
#endif
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;
		Viewport vp;
		vp.Width = (FLOAT)width;
		vp.Height = (FLOAT)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		cam->angle = 0.785398163f;
		cam->ratio = width / (FLOAT)height;
		cam->nearp = 0.01f;
		cam->farp = 600.0f;
		getmanager()->RSSetViewports(vp);//*/
		//XMMATRIX g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
		matrix cbChangesOnResize;
		//cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
		cam->getProyectionMatrixPerspective(cbChangesOnResize);
		//cbChangesOnResize.mProjection = cam->getProyectionMatrixPerspective(0.785398163f, width / (FLOAT)height, 0.01f, 100.0f);
#ifdef directX
		g_pImmediateContext->UpdateSubresource(chor.buf, 0, NULL, &cbChangesOnResize, 0, 0);
#endif
	}

	void DeviceContext::IASetPrimitiveTopology(PRIMITIVE_TOPOLOGY pt)
	{
#ifdef directX
		g_pImmediateContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)PRIMITIVE_TOPOLOGY::TRIANGLELIST);
#endif
	}

	void DeviceContext::ClearRenderTargetView(RenderTargetView& rtv,int n)
	{
#ifdef directX
		for(int i=0;i<n;i++)
		g_pImmediateContext->ClearRenderTargetView(rtv.get[i], rtv.ClearColor);
#endif
	}


	void DeviceContext::PSSetShaderResources(Textura* t,int cual)
	{
#ifdef directX
		g_pImmediateContext->PSSetShaderResources(cual, 1, &t->srv);
#endif
#ifdef openGL
		glActiveTexture(GL_TEXTURE0 + cual);
		glBindTexture(t->format, t->get);
#endif
	}

	void DeviceContext::OMSetRenderTargets(RenderTargetView& r, DepthStencil& d)
	{
#ifdef directX
		//g_pImmediateContext->OMSetRenderTargets(1, &r.get, d.view);
#endif
	}

	void DeviceContext::ClearDepthStencilView(DepthStencil& d)
	{
#ifdef directX
		g_pImmediateContext->ClearDepthStencilView(d.view, (D3D11_CLEAR_FLAG)CLEAR_FLAG::DEPTH, 1.0f, 0);
#endif
	}

	void DeviceContext::UpdateSubresource(Buffer& b, 
#ifdef directX
		const
#endif
		void* c) {
#ifdef openGL
		//b.Mem = &((matrix*)c)->m;
		b.data = *((glm::mat4*)c);
#endif
#ifdef directX
		g_pImmediateContext->UpdateSubresource(b.buf, 0, NULL, c, 0, 0);
#endif
	}

	void DeviceContext::VSSetShader(VertexShader& vs)
	{
#ifdef openGL
		vs.shader = glCreateShader(GL_VERTEX_SHADER);
#endif
#ifdef directX
		g_pImmediateContext->VSSetShader(vs.g_pVertexShader, NULL, 0);
#endif
	}

	/*void DeviceContext::PSSetShader(PixelShader& ps)
	{
#ifdef directX
		g_pImmediateContext->PSSetShader(ps.get(), NULL, 0);
#endif
	}*/

	void DeviceContext::IASetInputLayout(InputLayout& il)
	{
#ifdef directX
		g_pImmediateContext->IASetInputLayout(il.g_pVertexLayout);
#endif
	}

	void DeviceContext::draw(int n)
	{
#ifdef directX
		g_pImmediateContext->DrawIndexed(n, 0, 0);
#endif
	}

	DeviceContext::~DeviceContext()
	{
#ifdef directX
		g_pImmediateContext->Release();
#endif
	}

}
