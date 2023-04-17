/*============================================
DirectX11 Shader Lesson : common.hlsl 
"header file" for shaders )exclude from build)
Author: Sim Luigi
Last Updated: 2020.09.09
*============================================*/

// make sure to disable in build!
// Properties - General - ビルドから除外（はい）-ヘッダー扱い


//  Matrix Buffers
cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

cbuffer ViewBuffer : register(b1)
{
    matrix View;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}

//==========================
// 2020.09.09
// 下記の構造体の設定は.cppファイル (今回はrenderer.h) の内容と必ず一等にしよ！
// this struct must match the declaration in the .cpp file! (currently in renderer.h)

// マテリアルバッファ
// Material Buffer

// バイトアライン：バイト境界はあ16バイトじゃないと読み取れない (Windows)
// Byte Align: byte length must be in 16 byte increments (for Windows)
struct MATERIAL
{
    float4 Ambient;     
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float  Shininess; // 4 bytes; needs Dummy (+12 bytes)
    float3 Dummy;     // dummy 12bytes match 16 byte width required for struct
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL material;
}

//==========================
// 2020.09.09
// ライトバッファ
// Light Buffer


struct LIGHT
{
    bool    Enable;     // 4 bytes; needs Dummy (+12 bytes)
    bool3   Dummy;      // dummy 12 bytes to match 16 byte width (any type is ok, not just bool, but match type to associated variable for readability)
    float4  Direction;
    float4  Diffuse;
    float4  Ambient;
};

cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
}

// 2020.09.15
cbuffer CameraBuffer : register(b5)
{
    float4 CameraPosition;
}

cbuffer ParameterBuffer : register(b6)
{
    float4 Parameter;
}

//==========================
// 2020.09.01
// look up semantic: POSITION0, SV_POSITION, etc
// Struct to pass Vertex Shader
struct VS_IN
{
    float4 Position : POSITION0;  // zero position
    float4 Normal   : NORMAL0;
    float4 Diffuse  : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

// Struct to pass Index Shader
struct PS_IN
{
    float4 Position         : SV_POSITION;
    float4 WorldPosition    : POSITION0;
    float4 Normal           : NORMAL0;
    float4 Diffuse          : COLOR0;
    float2 TexCoord         : TEXCOORD0;
};

struct NF3D_LIGHT_OMNIDIRECTIONAL
{
    float4 Diffuse;
    float4 Ambient;
    float4 Position;
    float3 Altitude;
    float  Range;
    int    BindSlot;
};

cbuffer PointLightBuffer : register(b7)
{
    NF3D_LIGHT_OMNIDIRECTIONAL PointLight;
}