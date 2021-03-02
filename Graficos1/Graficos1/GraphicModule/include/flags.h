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
    enum class FORMAT {
        R32G32B32_FLOAT = 6,
        TYPELESS = 39,
        FLOAT =40
    };
    enum class USAGE
    {
        DEFAULT = 0,
        IMMUTABLE = 1,
        DYNAMIC = 2,
        STAGING = 3
    };
    enum class BIND_FLAG
    {
        VERTEX_BUFFER = 0x1L,
        INDEX_BUFFER = 0x2L,
        CONSTANT_BUFFER = 0x4L,
        SHADER_RESOURCE = 0x8L,
        STREAM_OUTPUT = 0x10L,
        RENDER_TARGET = 0x20L,
        DEPTH_STENCIL = 0x40L,
        UNORDERED_ACCESS = 0x80L
    };
    enum class DIMENSION
    {
        UNKNOWN = 0,
        TEXTURE1D = 1,
        TEXTURE1DARRAY = 2,
        TEXTURE2D = 3,
        TEXTURE2DARRAY = 4,
        TEXTURE2DMS = 5,
        TEXTURE2DMSARRAY = 6
    };
    enum class INPUT_C
    {
        VERTEX_DATA = 0,
        INSTANCE_DATA = 1
    };
}