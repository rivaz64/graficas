#include "Buffer.h"

Buffer::~Buffer()
{
    buf->Release();
}
