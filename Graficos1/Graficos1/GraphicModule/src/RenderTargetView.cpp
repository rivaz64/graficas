#include "..\include\RenderTargetView.h"

void GraphicsModule::RenderTargetView::setClearColor(std::initializer_list<float> c)
{
	///ClearColor = (float*)c.begin();
}

void GraphicsModule::RenderTargetView::release()
{
#ifdef  directX
	/*if (get) {
		*get->Release();
	}*/
	
#endif //  directX

	
}
