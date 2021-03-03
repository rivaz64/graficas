#include "Buffer.h"
namespace GraphicsModule {
	Buffer::~Buffer()
	{
		if(buf)
		buf->Release();
	}

}
