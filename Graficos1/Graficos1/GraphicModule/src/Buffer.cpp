#include "Buffer.h"
namespace GraphicsModule {
	Buffer::~Buffer()
	{
#ifdef directX
		if (buf)
			buf->Release();
#endif // directX

		
	}

}
