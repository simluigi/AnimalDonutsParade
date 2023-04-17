/*============================================
DirectX11 Shader Lesson : unlitTextureVS.hlsl
Unlit Texture Vertex Shader
Author: Sim Luigi
Last Updated: 2020.09.04
*============================================*/

// Right click - Properties: Shader Type: /vs　（頂点シェーダー）
// Remove $(OutDir) from Output File - Object File Name (only %(Filename).cso should remain)

#include "common.hlsl"
// In:  Vertex
// Out: Pixel

void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp; //world view projection
    wvp = mul(World, View); // mul: multiply via matrix math
    wvp = mul(wvp, Projection);
    
    Out.Position = mul(In.Position, wvp);
    
    //2020.09.04
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse;
}