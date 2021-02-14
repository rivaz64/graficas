#include "DeviceContext.h"
#include "camera.h"
void DeviceContext::OMSetRenderTargets(Device* v_device)
{
	dev = v_device;
	g_pImmediateContext->OMSetRenderTargets(1,&(v_device->g_pRenderTargetView) , v_device->DepthStencilView);
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
	g_pImmediateContext->IASetVertexBuffers(0, 1, &(dev->g_pVertexBuffer), &stride, &offset);
}

void DeviceContext::IASetIndexBuffer()
{
	g_pImmediateContext->IASetIndexBuffer(dev->g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void DeviceContext::UpdateSubresource(camera* cam)
{
	CBNeverChanges cbNeverChanges;
	cbNeverChanges.mView = cam->getview();
	g_pImmediateContext->UpdateSubresource(dev->g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);
}

void DeviceContext::resizewindow(camera* cam, UINT width, UINT height)
{
	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose( cam->getproyectionmatrixPerspective(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f) );
	g_pImmediateContext->UpdateSubresource(dev->g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0);
}

void DeviceContext::render(std::vector<float*>& instanses)
{
	
	g_pImmediateContext->VSSetShader(dev->vertexshader, NULL, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &dev->g_pCBNeverChanges);
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
		//cb.mWorld = XMMatrixTranspose(i);
		g_pImmediateContext->UpdateSubresource(dev->g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);
		g_pImmediateContext->DrawIndexed(36, 0, 0);
	}
}