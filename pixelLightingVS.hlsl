/*============================================
DirectX11 Shader Lesson : pixelLighitngVS.hlsl
(set as vertex shader, %Filename.cso)
Author: Sim Luigi
Last Updated: 2020.09.15

-Convert vertex data into pixel shader
-Set WorldPosition
*No need for light computation(i.e. Lambert, etc)
*============================================*/

#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    
    float4 worldNormal, normal; // float4 can be used with .xyz for coordinates, or .rgb for color
    normal = float4(In.Normal.xyz, 0.0);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);   // set length of normals to 1
    
    // Out.Position: actual 2D display on screen attained by coordinate conversion from 3d to 2dÅF ç¿ïWï‘ä“
    Out.Position = mul(In.Position, wvp);
    Out.WorldPosition = mul(In.Position, World);
    Out.Normal = worldNormal;
    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord;
}