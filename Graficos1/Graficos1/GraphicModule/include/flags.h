#pragma once

namespace GraphicsModule {
    enum class DRIVER_TYPE
    {
        DT_UNKNOWN = 0,
        DT_HARDWARE = (DT_UNKNOWN + 1),
        DT_REFERENCE = (DT_HARDWARE + 1),
        DT_NULL = (DT_REFERENCE + 1),
        DT_SOFTWARE = (DT_NULL + 1),
        DT_WARP = (DT_SOFTWARE + 1)
    };
    enum class FEATURE_LEVEL
    {
        LEVEL_9_1 = 0x9100,
        LEVEL_9_2 = 0x9200,
        LEVEL_9_3 = 0x9300,
        LEVEL_10_0 = 0xa000,
        LEVEL_10_1 = 0xa100,
        LEVEL_11_0 = 0xb000
    };
}