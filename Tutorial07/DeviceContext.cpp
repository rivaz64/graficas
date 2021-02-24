#include "DeviceContext.h"
#include "camera.h"
void DeviceContext::OMSetRenderTargets()
{
	g_pImmediateContext->OMSetRenderTargets(1,&(dev->g_pRenderTargetView) , dev->DepthStencilView);
}

void DeviceContext::RSSetViewports(UINT width, UINT height)
{
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &vp);
}

void DeviceContext::IASetInputLayout()
{
	g_pImmediateContext->IASetInputLayout(dev->g_pVertexLayout);
}

void DeviceContext::IASetVertexBuffers()
{
	UINT stride = sizeof(mesh::vertex);
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1, &(dev->vertexB.buf), &stride, &offset);
}

void DeviceContext::IASetIndexBuffer()
{
	g_pImmediateContext->IASetIndexBuffer(dev->indexB.buf, DXGI_FORMAT_R16_UINT, 0);
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void DeviceContext::UpdateSubresource(camera* cam)
{
	CBNeverChanges cbNeverChanges;
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
    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose(cam->getproyectionmatrixPerspective(0.785398163f, width / (FLOAT)height, 0.01f, 100.0f));
    g_pImmediateContext->UpdateSubresource(dev->g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0);
}

void DeviceContext::render(std::vector<float*>& instanses)
{
	
	g_pImmediateContext->VSSetShader(dev->vertexshader, NULL, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &dev->neverChangesB.buf);
	g_pImmediateContext->VSSetConstantBuffers(1, 1, &dev->g_pCBChangeOnResize);
	g_pImmediateContext->VSSetConstantBuffers(2, 1, &dev->g_pCBChangesEveryFrame);
	g_pImmediateContext->PSSetShader(dev->g_pPixelShader, NULL, 0);
	g_pImmediateContext->PSSetConstantBuffers(2, 1, &dev->g_pCBChangesEveryFrame);
	g_pImmediateContext->PSSetShaderResources(0, 1, &dev->g_pTextureRV);
	g_pImmediateContext->PSSetSamplers(0, 1, &dev->g_pSamplerLinear);
	CBChangesEveryFrame cb;
	cb.vMeshColor = g_vMeshColor;
	g_pImmediateContext->ClearRenderTargetView(dev->g_pRenderTargetView, ClearColor);
	g_pImmediateContext->ClearDepthStencilView(dev->DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	for (float* i : instanses) {
		cb.mWorld = XMMatrixTranspose(i);
		g_pImmediateContext->UpdateSubresource(dev->g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);
		g_pImmediateContext->DrawIndexed(36, 0, 0);
	}
}
