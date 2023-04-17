/*============================================
DirectX11 Shader Lesson : unlitTexturePS.hlsl
Unlit Texture Pixel Shader
Author: Sim Luigi
Last Updated: 2020.09.04
*============================================*/

// Set as Pixel Shader
// Right click - Properties: Shader Type: /ps　（ピクセルシェーダー）
// Remove $(OutDir) from Output File - Object File Name (only %(Filename).cso should remain)

#include "common.hlsl"

// global variables
// グローバル変数
Texture2D g_Texture : register(t0); // texture 0 (can use multiple for multiple textures)
SamplerState g_SamplerState : register(s0); // state 0

// calculates PER PIXEL; avoid using conditional statements or system processing speed plummets
// 1ピクセルごと処理：if分などを使うと処理速度がかなり低下！使わない方がいい

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{    
    // texture mapping
    //　テクスチャーマッピング
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse *= In.Diffuse;
    
}
