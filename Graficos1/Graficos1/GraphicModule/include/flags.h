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
        UNKNOWN = 0,
        R32G32B32A32_FLOAT = 2,
        R32G32B32_FLOAT = 6,
        R8G8B8A8_UNORM = 28,
        TYPELESS = 39,
        FLOAT =40,
        R32_UINT = 42,
        UNORM_S8_UINT = 45,
        R16_UINT = 57,
    };
    enum class USAGE
    {
        DEFAULT 
#ifdef openGL
         =0x88E4
#endif
#ifdef directX
         =0
#endif
        ,
        IMMUTABLE = 1,
        DYNAMIC = 2,
        STAGING = 3
    };
    enum class BIND_FLAG
    {
        VERTEX_BUFFER 
#ifdef openGL
         =0x8892
#endif
#ifdef directX
         =0x1L
#endif
        ,
        INDEX_BUFFER
#ifdef openGL
        = 0x8893
#endif
#ifdef directX
        = 0x2L
#endif
        ,
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
        TEXTURE2DMSARRAY = 6,
        TEXTURECUBE = 9,
    };
    enum class SRV_DIMENSION
    {
        
        TEXTURE2D = 4,
        TEXTURECUBE = 9,
    };
    enum class INPUT_C
    {
        VERTEX_DATA = 0,
        INSTANCE_DATA = 1
    };
    enum class FILTER
    {
        MIN_MAG_MIP_POINT = 0,
        MIN_MAG_POINT_MIP_LINEAR = 0x1,
        MIN_POINT_MAG_LINEAR_MIP_POINT = 0x4,
        MIN_POINT_MAG_MIP_LINEAR = 0x5,
        MIN_LINEAR_MAG_MIP_POINT = 0x10,
        MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
        MIN_MAG_LINEAR_MIP_POINT = 0x14,
        MIN_MAG_MIP_LINEAR = 0x15,
        ANISOTROPIC = 0x55,
        COMPARISON_MIN_MAG_MIP_POINT = 0x80,
        COMPARISON_MIN_MAG_POINT_MIP_LINEAR = 0x81,
        COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x84,
        COMPARISON_MIN_POINT_MAG_MIP_LINEAR = 0x85,
        COMPARISON_MIN_LINEAR_MAG_MIP_POINT = 0x90,
        COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x91,
        COMPARISON_MIN_MAG_LINEAR_MIP_POINT = 0x94,
        COMPARISON_MIN_MAG_MIP_LINEAR = 0x95,
        COMPARISON_ANISOTROPIC = 0xd5
    };
    enum class ADDRESS_MODE
    {
        WRAP = 1,
        MIRROR = 2,
        CLAMP = 3,
        BORDER = 4,
        MIRROR_ONCE = 5
    };
    enum class COMPARISON_FUNC{
        NEVER = 1,
        LESS = 2,
   EQUAL = 3,
   LESS_EQUAL = 4,
   GREATER = 5,
   NOT_EQUAL = 6,
   GREATER_EQUAL = 7,
   ALWAYS = 8
    };
    
    enum class  CLEAR_FLAG
    {
       DEPTH = 0x1L,
        STENCIL = 0x2L
    };
    enum class PRIMITIVE_TOPOLOGY {
        UNDEFINED = 0,
        POINTLIST = 1,
        LINELIST = 2,
        LINESTRIP = 3,
        TRIANGLELIST = 4,
        TRIANGLESTRIP = 5,
        LINELIST_ADJ = 10,
        LINESTRIP_ADJ = 11,
        TRIANGLELIST_ADJ = 12,
        TRIANGLESTRIP_ADJ = 13,
       
    };
}