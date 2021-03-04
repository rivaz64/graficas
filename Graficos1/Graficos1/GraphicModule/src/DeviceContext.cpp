#include "DeviceContext.h"
#include "camera.h"
#include"test.h"
#include"Viewport.h"
namespace GraphicsModule {
	

	void DeviceContext::RSSetViewports(UINT width, UINT height)
	{
		Viewport vp;
		//D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)width;
		vp.Height = (FLOAT)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		g_pImmediateContext->RSSetViewports(1, (D3D11_VIEWPORT*)(&vp));
	}

	void DeviceContext::IASetInputLayout()
	{
		g_pImmediateContext->IASetInputLayout(dev->g_pVertexLayout);
	}

	void DeviceContext::IASetVertexBuffers(Buffer* b)
	{
		UINT stride = sizeof(mesh::vertex);
		UINT offset = 0;
		g_pImmediateContext->IASetVertexBuffers(0, 1, &(b->buf), &stride, &offset);
	}


	void DeviceContext::IASetIndexBuffer(Buffer* b)
	{
		g_pImmediateContext->IASetIndexBuffer(b->buf, (DXGI_FORMAT)FORMAT::R16_UINT, 0);
	}

	void DeviceContext::UpdateSubresource(camera* cam)
	{
		GraphicsModule::CBNeverChanges cbNeverChanges;
		cbNeverChanges.mView = XMMatrixTranspose(cam->getview());
		g_pImmediateContext->UpdateSubresource(dev->neverChangesB.buf, 0, NULL, &cbNeverChanges, 0, 0);
	}

	void DeviceContext::UpdateView(camera* cam)
	{
		/*CBChangesEveryFrame cbChangesEveryFrame;
		cbChangesEveryFrame.mView = XMMatrixTranspose(cam->getview());
		g_pImmediateContext->UpdateSubresource(dev->g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);*/
	}

	void DeviceContext::resizewindow(camera* cam, HWND& g_hWnd)
	{
		g_pImmediateContext->OMSetRenderTargets(1, &dev->g_pRenderTargetView, NULL);
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)width;
		vp.Height = (FLOAT)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		g_pImmediateContext->RSSetViewports(1, &vp);
		GraphicsModule::CBChangeOnResize cbChangesOnResize;
		cbChangesOnResize.mProjection = XMMatrixTranspose(cam->getproyectionmatrixPerspective(0.785398163f, width / (FLOAT)height, 0.01f, 100.0f));
		g_pImmediateContext->UpdateSubresource(dev->changesOnReziseB.buf, 0, NULL, &cbChangesOnResize, 0, 0);
	}

	void DeviceContext::IASetPrimitiveTopology(PRIMITIVE_TOPOLOGY pt)
	{
		g_pImmediateContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)PRIMITIVE_TOPOLOGY::TRIANGLELIST);
	}


	void DeviceContext::PSSetShaderResources(Textura* t)
	{
		g_pImmediateContext->PSSetShaderResources(0, 1, &t->srv);
	}

	void DeviceContext::OMSetRenderTargets(RenderTargetView& r, DepthStencil& d)
	{
		g_pImmediateContext->OMSetRenderTargets(1, &r.get, d.view);
	}

	void DeviceContext::ClearDepthStencilView(DepthStencil& d)
	{
		g_pImmediateContext->ClearDepthStencilView(d.view, (D3D11_CLEAR_FLAG)CLEAR_FLAG::DEPTH, 1.0f, 0);
	}

	

	void DeviceContext::draw()
	{
		g_pImmediateContext->DrawIndexed(36, 0, 0);
	}

}
