#include "Buffer.h"
namespace GraphicsModule {
	void Buffer::describe()
	{

	}
	Buffer::~Buffer()
	{
#ifdef directX
		if (buf)
			buf->Release();
#endif // directX

		
	}

}
