#include "viewport.h"

void viewport::release()
{
    g_pRenderTargetView->Release();
}
