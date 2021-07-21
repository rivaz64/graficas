#include "Buffer.h"
#include"manager.h"
namespace GraphicsModule {
	void Buffer::init()
	{
#ifdef openGL

		glGenBuffers(1, &buf);
		glBindBuffer((GLenum)BindFlags, buf);
		glBufferData((GLenum)BindFlags, ByteWidth, Mem, (GLenum)Usage);

#endif
#ifdef directX
		D3D11_BUFFER_DESC bd;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&bd, sizeof(bd));
		ZeroMemory(&InitData, sizeof(InitData));
		bd.Usage = (D3D11_USAGE)Usage;
		bd.ByteWidth = ByteWidth;
		bd.BindFlags = (D3D11_BIND_FLAG)BindFlags;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = Mem;
		if (Mem == NULL)
			getmanager()->getDevice()->get()->CreateBuffer(&bd, NULL, &buf);
		else
			getmanager()->getDevice()->get()->CreateBuffer(&bd, &InitData, &buf);
#endif
	}
	void Buffer::update(void* c)
	{
#ifdef openGL
		data = *((glm::mat4*)c);
#endif
#ifdef directX
		getmanager()->getConext()->get()->UpdateSubresource(buf, 0, NULL, c, 0, 0);
#endif
	}
}
